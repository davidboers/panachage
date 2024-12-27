@echo off
gcc -c ../ham.c -o ham.o
if not %ERRORLEVEL% == 0 goto Complete
echo Compiled HAM library
ar rcs libham.a ham.o
echo Compiling test
g++ liechtenstein.cpp -L. -lham -o liechtenstein
if not %ERRORLEVEL% == 0 goto Complete
echo Test successfully compiled
liechtenstein

:Complete