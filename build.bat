@echo off
setlocal enabledelayedexpansion

REM === SETTINGS ===
set COMPILER=g++
set SRC_DIR=src
set INCLUDE_DIR=include
set RAYLIB_INCLUDE=C:/raylib/include
set RAYLIB_LIB=C:/raylib/lib
set OUTPUT_DIR=bin
set OUTPUT=%OUTPUT_DIR%/collision-sim.exe

REM === CREATE OUTPUT DIR IF NOT EXIST ===
if not exist %OUTPUT_DIR% (
    mkdir %OUTPUT_DIR%
    echo Created output folder: %OUTPUT_DIR%
)

REM === COLLECT ALL .CPP RECURSIVELY ===
echo Searching for .cpp files...
set FILES=

for /R %SRC_DIR% %%f in (*.cpp) do (
    set FILES=!FILES! "%%f"
)

echo Found files:
echo !FILES!
echo.

REM === COMPILE ===
echo Compiling...
%COMPILER% !FILES! ^
    -I %INCLUDE_DIR% ^
    -I %RAYLIB_INCLUDE% ^
    -L %RAYLIB_LIB% ^
    -lraylib -lopengl32 -lgdi32 -lwinmm ^
    -std=c++17 ^
    -o %OUTPUT%

echo -----------------------------------------
if exist %OUTPUT% (
    echo BUILD SUCCESS! Output: %OUTPUT%
) else (
    echo BUILD FAILED!
)
echo -----------------------------------------

pause
endlocal
