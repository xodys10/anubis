@echo off
:: generate vc vars for cmake, or else cmake will annoy you
:: since cmd halts on everything once you run vcvarsall, you need to run it yourself

:: clean up previous builds
rmdir /s /q "build" 2>nul
rmdir /s /q "CMakeFiles" 2>nul
rmdir /s /q "Debug" 2>nul
rmdir /s /q "Release" 2>nul
rmdir /s /q "out" 2>nul
rmdir /s /q "x64" 2>nul
del /q "CMakeCache.txt" 2>nul

:: now, generate build files
:: since we specified vs2019, use vs2019
cmake -G "Visual Studio 17 2022" -A x64 .
cmake --build . --config Debug