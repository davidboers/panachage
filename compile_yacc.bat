flex votes.l
bison -dy votes.y

if "%1" == "test" goto Test
goto Complete

:Test
cd tests
g++ votefile.cpp -o votefile
votefile
echo %ERRORLEVEL%
cd ..

:Complete