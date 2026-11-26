// Decompiles every function whose entry lies in [from, to) into one C file.
// Usage (headless): -postScript DecompileRange.java <from hex> <to hex> <output dir>
//@category KartRE

import java.io.File;
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class DecompileRange extends GhidraScript {

    private static final int TIMEOUT_SECONDS = 120;

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) {
            printerr("usage: DecompileRange.java <from hex> <to hex> <output dir>");
            return;
        }
        Address from = toAddr(Long.parseLong(args[0], 16));
        Address to = toAddr(Long.parseLong(args[1], 16));
        File outDir = new File(args[2]);
        outDir.mkdirs();
        File outFile = new File(outDir, "decomp_" + args[0] + "_" + args[1] + ".c");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        int done = 0;
        int failed = 0;
        try (PrintWriter out = new PrintWriter(outFile, "UTF-8")) {
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(from, true);
            while (it.hasNext() && !monitor.isCancelled()) {
                Function f = it.next();
                if (f.getEntryPoint().compareTo(to) >= 0) {
                    break;
                }
                out.printf("%n/* ==== %s  %s  size=%d ==== */%n", f.getEntryPoint(), f.getName(),
                        f.getBody().getNumAddresses());
                DecompileResults res = decomp.decompileFunction(f, TIMEOUT_SECONDS, monitor);
                if (res.decompileCompleted()) {
                    out.println(res.getDecompiledFunction().getC());
                    done++;
                }
                else {
                    out.println("/* decompile failed: " + res.getErrorMessage() + " */");
                    failed++;
                }
            }
        }
        finally {
            decomp.dispose();
        }
        println(String.format("DecompileRange: %d ok, %d failed -> %s", done, failed, outFile));
    }
}
