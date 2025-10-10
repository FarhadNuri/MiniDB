@echo off
echo Running Database Engine Tests...

REM Build first if needed
if not exist database_engine.exe (
    echo Building database engine first...
    call build.bat
    if errorlevel 1 (
        echo Build failed! Cannot run tests.
        exit /b 1
    )
)

echo.
echo === Basic Operations Test ===
database_engine.exe < tests/basic_operations.sql

echo.
echo === Advanced Operations Test ===
database_engine.exe < tests/advanced_operations.sql

echo.
echo === Performance Test ===
database_engine.exe < tests/performance_test.sql

echo.
echo All tests completed!