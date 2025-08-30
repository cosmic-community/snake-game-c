@echo off
REM build.bat

echo Building Snake Game...

REM Create build directory if it doesn't exist
if not exist "build" mkdir build

REM Navigate to build directory
cd build

REM Configure with CMake
echo Configuring project...
cmake ..

REM Check if configuration was successful
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build the project
echo Compiling...
cmake --build . --config Release

REM Check if build was successful
if %ERRORLEVEL% equ 0 (
    echo Build successful!
    echo Run the game with: SnakeGame.exe
) else (
    echo Build failed!
)

pause