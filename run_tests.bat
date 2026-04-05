@echo off
setlocal

cd /d "%~dp0"

echo Building compiler...
bison -d -o parser.tab.c parser.y
if errorlevel 1 goto :fail

flex scanner.l
if errorlevel 1 goto :fail

gcc -Wall -Wextra -o compiler.exe parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c -lm
if errorlevel 1 goto :fail

set "choice=%~1"
if not defined choice goto :prompt
goto :dispatch

:prompt
echo.
echo Select a test to run:
echo   1  - t01_decl.txt
echo   2  - t02_expr.txt
echo   3  - t03_io.txt
echo   4  - t04_cond.txt
echo   5  - t05_loops.txt
echo   6  - t06_text.txt
echo   7  - t07_funcs.txt
echo   8  - t08_decide.txt
echo   9  - t09_scope.txt
echo   10 - t10_full.txt
echo   11 - t11_rec.txt
echo   12 - t12_nested.txt
echo   all - run every test
echo.
set /p choice=Enter a number, file name, or all: 

:dispatch
if /I "%choice%"=="all" goto :run_all
if /I "%choice%"=="1" goto :run_01
if /I "%choice%"=="2" goto :run_02
if /I "%choice%"=="3" goto :run_03
if /I "%choice%"=="4" goto :run_04
if /I "%choice%"=="5" goto :run_05
if /I "%choice%"=="6" goto :run_06
if /I "%choice%"=="7" goto :run_07
if /I "%choice%"=="8" goto :run_08
if /I "%choice%"=="9" goto :run_09
if /I "%choice%"=="10" goto :run_10
if /I "%choice%"=="11" goto :run_11
if /I "%choice%"=="12" goto :run_12

if exist "%choice%" goto :run_custom
if exist "tests\%choice%" (
    set "choice=tests\%choice%"
    goto :run_custom
)

echo.
echo Invalid selection: %choice%
exit /b 1

:run_all
echo.
echo Running all tests...
call :run "tests\t01_decl.txt"
call :run "tests\t02_expr.txt"
call :prompt_input "tests\t03_io.txt"
call :run "tests\t04_cond.txt"
call :run "tests\t05_loops.txt"
call :run "tests\t06_text.txt"
call :run "tests\t07_funcs.txt"
call :run "tests\t08_decide.txt"
call :run "tests\t09_scope.txt"
call :run "tests\t10_full.txt"
call :run "tests\t11_rec.txt"
call :run "tests\t12_nested.txt"
goto :done

:run_01
call :run "tests\t01_decl.txt"
goto :done

:run_02
call :run "tests\t02_expr.txt"
goto :done

:run_03
call :prompt_input "tests\t03_io.txt"
goto :done

:run_04
call :run "tests\t04_cond.txt"
goto :done

:run_05
call :run "tests\t05_loops.txt"
goto :done

:run_06
call :run "tests\t06_text.txt"
goto :done

:run_07
call :run "tests\t07_funcs.txt"
goto :done

:run_08
call :run "tests\t08_decide.txt"
goto :done

:run_09
call :run "tests\t09_scope.txt"
goto :done

:run_10
call :run "tests\t10_full.txt"
goto :done

:run_11
call :run "tests\t11_rec.txt"
goto :done

:run_12
call :run "tests\t12_nested.txt"
goto :done

:run_custom
if /I "%choice%"=="tests\t03_io.txt" (
    call :prompt_input "%choice%"
) else (
    call :run "%choice%"
)
goto :done

:done
echo.
echo Finished.
exit /b 0

:run
echo.
echo === %~1 ===
.\compiler.exe %~1
if errorlevel 1 echo ExitCode: %errorlevel%
exit /b 0

:prompt_input
set "test_input=7"
echo.
set /p test_input=Enter input for %~1 [default 7]: 
if "%test_input%"=="" set "test_input=7"
call :run_input "%~1" "%test_input%"
exit /b 0

:run_input
echo.
echo === %~1 ===
echo %~2|.\compiler.exe %~1
if errorlevel 1 echo ExitCode: %errorlevel%
exit /b 0

:fail
echo.
echo Build failed.
exit /b 1
