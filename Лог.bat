﻿@echo off
chcp 65001 >nul
cd /d "%~dp0"

if not exist "logs" (
    echo   Логов пока нет — сервер ещё ни разу не запускался.
    pause
    exit /b 1
)

rem ---- берём самый свежий файл лога
set "LAST="
for /f "delims=" %%F in ('dir /b /o-d "logs\marshal-*.log" 2^>nul') do (
    if not defined LAST set "LAST=%%F"
)

if not defined LAST (
    echo   Логов пока нет.
    pause
    exit /b 1
)

start "Лог SmartKart" powershell -NoExit -Command ^
  "$host.UI.RawUI.WindowTitle='Лог SmartKart — %LAST%';" ^
  "Get-Content -LiteralPath '%~dp0logs\%LAST%' -Encoding UTF8 -Tail 60 -Wait"

exit /b 0
