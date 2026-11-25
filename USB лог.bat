@echo off
set /p KART=Kart number: 
py -I "%~dp0usb_log.py" --kart %KART%
pause
