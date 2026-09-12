@echo off
chcp 65001 >nul
cd /d "%~dp0"
title Автозапуск SmartKart

echo.
echo   Настройка автозапуска при входе в Windows.
echo.
choice /c YN /m "1 - включить, 2 - выключить"
if errorlevel 2 goto off

powershell -NoProfile -Command ^
  "$p=[Environment]::GetFolderPath('Startup') + '\SmartKart.lnk';" ^
  "$s=(New-Object -COM WScript.Shell).CreateShortcut($p);" ^
  "$s.TargetPath='%~dp0Картинг.bat';" ^
  "$s.WorkingDirectory='%~dp0';" ^
  "$s.WindowStyle=7;" ^
  "$s.Description='Сервер картов SmartKart';" ^
  "$s.Save();" ^
  "Write-Host '  Автозапуск включён:' $p"
echo.
echo   Теперь сервер поднимается сам при входе в систему.
echo   Проверка: перезагрузи ПК и просто подожди полминуты.
pause
exit /b 0

:off
powershell -NoProfile -Command ^
  "$p=[Environment]::GetFolderPath('Startup') + '\SmartKart.lnk';" ^
  "if (Test-Path $p) { Remove-Item $p; Write-Host '  Автозапуск выключен.' }" ^
  "else { Write-Host '  Автозапуск и так не был включён.' }"
pause
exit /b 0
