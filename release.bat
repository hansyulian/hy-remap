mkdir -p build/release
xcopy /-I /Y "config.json" "build\release\config.json" 
cd build/release
conan install ../.. --output-folder=. --build=missing -s compiler="gcc" -s compiler.libcxx=libstdc++11  -s build_type=Release
cmake ../.. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
cmake --build .
cd ../..
