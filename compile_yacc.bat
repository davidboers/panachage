flex -o partylist_lexer.c partylist.l
flex -o votes_lexer.c votes.l
bison -dy partylist.y -b partylist
bison -dy votes.y -b votes

if "%1" == "test" goto Test
goto Complete

:Test
cd tests
g++ votefile.cpp -o votefile
votefile
echo %ERRORLEVEL%
cd ..

:Complete