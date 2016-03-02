REM without parameters
lab2.exe
IF NOT ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

REM 1 not number parameter
lab2.exe notANumber 12 123
IF NOT ERRORLEVEL 2 GOTO err
ECHO Program testing succeeded :-)

REM one of the parameters exceed the allowed notation
lab2.exe 2 37 1010
IF NOT ERRORLEVEL 2 GOTO err
ECHO Program testing succeeded :-)

REM number exceed the allowed notation
lab2.exe 2 10 1012
IF NOT ERRORLEVEL 3 GOTO err
ECHO Program testing succeeded :-)

REM run program
lab2.exe 2 10 1011 > output.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output.txt 1011.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

REM run program
lab2.exe 36 10 Z > output.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output.txt Z.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

REM run program with the negative number
lab2.exe 36 10 -Z > output.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output.txt -Z.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

REM run program with big number
lab2.exe 36 3 -ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ > output.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output.txt -ZZZZZZZZZZZZ.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded :-)

@PAUSE
EXIT

:err
ECHO Program testing failed :-(
@PAUSE
EXIT
