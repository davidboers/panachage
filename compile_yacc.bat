@echo off
flex -o partylist_lexer.c partylist.l
flex -o votes_lexer.c votes.l
bison -dy partylist.y -b partylist
bison -dy votes.y -b votes

if "%1" == "test" goto Test
goto Complete

:Test
cd tests

echo Compiling votefile.cpp...
g++ votefile.cpp -o votefile
echo Executing votefile.exe...
votefile
echo Error level:
echo %ERRORLEVEL%

echo Compiling partylistfile.cpp...
g++ partylistfile.cpp -o partylistfile
echo Executing partylistfile.exe...
partylistfile
echo Error level:
echo %ERRORLEVEL%

cd ..

:Complete