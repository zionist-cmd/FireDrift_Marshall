@echo off
chcp 65001 >nul
title Остановка SmartKart

echo.
echo   ВНИМАНИЕ: карты, которые сейчас едут, доедут своё время сами
echo   и погаснут. Но панель их потеряет.
echo.
echo   Останавливать только между группами.
echo.
choice /c YN /m "Остановить сервер"
if errorlevel 2 exit /b 0

rem Сначала окно с циклом, иначе оно поднимет сервер заново
taskkill /fi "WINDOWTITLE eq SmartKart сервер*" /t /f >nul 2>&1
for /f "tokens=5" %%P in ('netstat -ano ^| find ":8080" ^| find "LISTENING"') do taskkill /pid %%P /f >nul 2>&1

echo.
echo   Сервер остановлен.
timeout /t 2 /nobreak >nul
exit /b 0
