cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
mingw32-make.exe
call HRemap.exe
cd ..