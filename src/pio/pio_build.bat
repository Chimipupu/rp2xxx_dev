@REM @echo off
@REM set PIOASM_PATH=%~dp0pqt-pioasm\4.0.1-8ec9d6f
@REM %PIOASM_PATH%\pioasm.exe %1 > %1.h
pioasm.exe %1 > %1.h
@REM pause