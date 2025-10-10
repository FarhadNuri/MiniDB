@echo off
echo Building In-Memory Database Engine...

REM Clean previous build
if exist database_engine.exe del database_engine.exe
if exist src\*.o del src\*.o

REM Compile source files
echo Compiling main.cpp...
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude -c src/main.cpp -o src/main.o
if errorlevel 1 goto error

echo Compiling database.cpp...
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude -c src/database.cpp -o src/database.o
if errorlevel 1 goto error

echo Compiling table.cpp...
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude -c src/table.cpp -o src/table.o
if errorlevel 1 goto error

echo Compiling index.cpp...
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude -c src/index.cpp -o src/index.o
if errorlevel 1 goto error

REM Link executable
echo Linking database_engine.exe...
g++ -std=c++17 -Wall -Wextra -O2 -o database_engine.exe src/main.o src/database.o src/table.o src/index.o
if errorlevel 1 goto error

echo.
echo Build successful! Run 'database_engine.exe' to start the database.
goto end

:error
echo.
echo Build failed! Please check the error messages above.
exit /b 1

:end