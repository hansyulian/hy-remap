mkdir "build\release"
xcopy "config.json" "build\release\config.json" /F /Y
cd build/release
cmake ../.. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
mingw32-make.exe
cd ../..