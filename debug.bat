mkdir "build\debug"
xcopy "config.json" "build\debug\config.json" /F /Y
cd build/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
mingw32-make.exe
cd ../..