chcp 1251

REM without parameters
lab1.exe
@IF NOT ERRORLEVEL 1 GOTO err

REM incorrect parameters count
lab1.exe input.txt output.txt 1231234 12312312345 18
@IF NOT ERRORLEVEL 1 GOTO err

REM input file doesn't exist
lab1.exe pop.txt output.txt 1231234 12312312345
@IF NOT ERRORLEVEL 2 GOTO err

REM correct replacing 1231234 in 12312312345
lab1.exe test/input.txt test/output1231234-paul.txt 1231234 paul
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\output1231234-paul.txt test\1231234-paul.txt
@IF ERRORLEVEL 1 GOTO err

REM correct replacing 1231234 in 12312312345
lab1.exe test/input.txt test/output1231234-12312312345.txt 1231234 12312312345
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\output1231234-12312312345.txt test\1231234-12312312345.txt
@IF ERRORLEVEL 1 GOTO err

REM searching text doesn't exist
lab1.exe test/input.txt test/output12312312345.txt voodoo 12312312345
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\output12312312345.txt test\12312312345.txt
@IF ERRORLEVEL 1 GOTO err

REM big russian text
lab1.exe test/input1.txt test/output1.txt мама мать
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\output1.txt test\bigrussian.txt
@IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
@PAUSE
EXIT

:err
ECHO Program testing failed :-(
@PAUSE
EXIT
