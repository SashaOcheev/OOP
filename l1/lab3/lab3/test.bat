chcp 1251

@REM without parameters
lab3.exe
@IF NOT ERRORLEVEL 1 GOTO err

@REM incorrect parameters count
lab3.exe input.txt output.txt 1231234 12312312345 18
@IF NOT ERRORLEVEL 1 GOTO err

@REM input file doesn't exist
lab3.exe pop.txt
@IF NOT ERRORLEVEL 2 GOTO err

@REM not number matrix
lab3.exe test\incorrectMatrixFormat.txt
@IF NOT ERRORLEVEL 3 GOTO err

@REM incorrect matrix size
lab3.exe test\incorrectSize.txt
@IF NOT ERRORLEVEL 4 GOTO err

@REM determinantIs0
lab3.exe test/determinantIs0.txt > test\determinantIs0Res.txt
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\determinantIs0Res.txt test\determinantIs0Et.txt
@IF ERRORLEVEL 1 GOTO err

@REM correct 3*3
lab3.exe test/matrix.txt > test\matrixRes.txt
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\matrixRes.txt test\matrixEt.txt
@IF ERRORLEVEL 1 GOTO err

@REM correct 5*5
lab3.exe test/matrix5.txt > test\matrix5Res.txt
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\matrix5Res.txt test\matrix5Et.txt
@IF ERRORLEVEL 1 GOTO err

@REM correct 10*10
lab3.exe test/matrix10.txt > test\matrix10Res.txt
@IF NOT ERRORLEVEL 0 GOTO err
@FC /B test\matrix10Res.txt test\matrix10Et.txt
@IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
@PAUSE
EXIT

:err
ECHO Program testing failed :-(
@PAUSE
EXIT
