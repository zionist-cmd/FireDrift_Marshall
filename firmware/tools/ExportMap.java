// Exports a map of the analyzed firmware: functions, and the 32-bit constants each
// function loads through l32r literal pools (string addresses, globals, callees).
// Usage (headless): -postScript ExportMap.java <output dir>
//@category KartRE

import java.io.File;
import java.io.PrintWriter;
import java.util.TreeSet;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryAccessException;
import ghidra.program.model.symbol.Reference;

public class ExportMap extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File outDir = new File(args.length > 0 ? args[0] : ".");
        outDir.mkdirs();
        Memory mem = currentProgram.getMemory();

        try (PrintWriter funcs = new PrintWriter(new File(outDir, "functions.tsv"), "UTF-8");
             PrintWriter consts = new PrintWriter(new File(outDir, "fn_constants.tsv"), "UTF-8")) {
            funcs.println("entry\tsize\tname\tcallers\tcallees");
            consts.println("function\tinsn\tliteral\tvalue");
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            while (it.hasNext() && !monitor.isCancelled()) {
                Function f = it.next();
                funcs.printf("%s\t%d\t%s\t%d\t%d%n", f.getEntryPoint(), f.getBody().getNumAddresses(),
                        f.getName(), f.getCallingFunctions(monitor).size(),
                        f.getCalledFunctions(monitor).size());
                exportConstants(f, mem, consts);
            }
        }
        println("ExportMap done: " + outDir.getAbsolutePath());
    }

    private void exportConstants(Function f, Memory mem, PrintWriter out) {
        TreeSet<String> seen = new TreeSet<>();
        InstructionIterator insns = currentProgram.getListing().getInstructions(f.getBody(), true);
        while (insns.hasNext()) {
            Instruction insn = insns.next();
            if (!insn.getMnemonicString().startsWith("l32r")) {
                continue;
            }
            for (Reference ref : insn.getReferencesFrom()) {
                Address lit = ref.getToAddress();
                if (!lit.isMemoryAddress() || !mem.contains(lit)) {
                    continue;
                }
                try {
                    long value = mem.getInt(lit) & 0xffffffffL;
                    String row = String.format("%s\t%s\t%s\t%08x", f.getEntryPoint(), insn.getAddress(), lit, value);
                    if (seen.add(row)) {
                        out.println(row);
                    }
                }
                catch (MemoryAccessException e) {
                    // literal in an uninitialized block: nothing to read
                }
            }
        }
    }
}
