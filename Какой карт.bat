@echo off
cd /d "%~dp0"
where py >nul 2>nul
if errorlevel 1 (
    python kakoy_kart.py %*
) else (
    py kakoy_kart.py %*
)
pause
