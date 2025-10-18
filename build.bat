@echo off
:: cleanup previous builds
rmdir /s /q "build" 2>nul
rmdir /s /q "CMakeFiles" 2>nul
rmdir /s /q "Debug" 2>nul
rmdir /s /q "Release" 2>nul
rmdir /s /q "out" 2>nul
rmdir /s /q "x64" 2>nul
del /q "CMakeCache.txt" 2>nul

:: now, generate build files
cmake -G "Visual Studio 17 2022" -A x64 .
cmake --build . --config Debug
