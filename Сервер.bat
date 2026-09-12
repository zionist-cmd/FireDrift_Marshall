@echo off
chcp 65001 >nul
cd /d "%~dp0"
title SmartKart сервер

rem Этот файл руками не запускают — его поднимает «Картинг.bat».
rem Здесь цикл: если python по какой-то причине завершился, сервер
rem поднимается заново через 5 секунд. Смена не должна вставать
rem из-за одной ошибки.

set "PY="
for /f "delims=" %%I in ('where python.exe 2^>nul') do if not defined PY set "PY=%%I"
if not defined PY for /f "delims=" %%I in ('where py.exe 2^>nul') do if not defined PY set "PY=%%I"
if not defined PY (
    echo   ОШИБКА: Python не найден. Установи с python.org, галочка "Add to PATH".
    pause
    exit /b 1
)

:loop
echo.
echo   [%date% %time%] запуск marshal.py
"%PY%" "%~dp0marshal.py"
echo.
echo   [%date% %time%] сервер завершился. Перезапуск через 5 секунд.
echo   Чтобы остановить совсем — закрой это окно или запусти «Стоп.bat».
timeout /t 5 /nobreak >nul
goto loop
