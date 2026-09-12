@echo off
chcp 65001 >nul
cd /d "%~dp0"
title Запуск SmartKart

echo.
echo   Запускаю сервер картов...
echo.

netstat -an | find ":8080" | find "LISTENING" >nul
if not errorlevel 1 (
    echo   Сервер уже работает. Открываю панель.
    start "" http://localhost:8080/
    exit /b 0
)

if not exist "%~dp0Сервер.bat" (
    echo   ОШИБКА: рядом нет файла «Сервер.bat».
    pause
    exit /b 1
)

start "SmartKart сервер" /min cmd /c ""%~dp0Сервер.bat""

set /a TRY=0
:wait
timeout /t 1 /nobreak >nul
set /a TRY+=1
netstat -an | find ":8080" | find "LISTENING" >nul
if not errorlevel 1 goto ready
if %TRY% lss 25 goto wait

echo.
echo   Сервер не поднялся за 25 секунд. Открываю папку с логом.
start "" "%~dp0logs"
pause
exit /b 1

:ready
echo   Готово. Открываю панель маршала.
start "" http://localhost:8080/
exit /b 0
