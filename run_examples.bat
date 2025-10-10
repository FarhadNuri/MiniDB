@echo off
echo Running Database Engine Examples...

REM Build first if needed
if not exist database_engine.exe (
    echo Building database engine first...
    call build.bat
    if errorlevel 1 (
        echo Build failed! Cannot run examples.
        exit /b 1
    )
)

echo.
echo === University Database Demo ===
database_engine.exe < examples/university_demo.sql

echo.
echo === E-commerce Database Demo ===
database_engine.exe < examples/ecommerce_demo.sql

echo.
echo All examples completed!