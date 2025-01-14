mkdir -p build/debug
xcopy /-I /Y "config.json" "build\debug\config.json"
cd build/debug
conan install ../.. --output-folder=. --build=missing -s compiler="gcc" -s compiler.libcxx=libstdc++11 -s build_type=Debug
cmake ../.. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
cmake --build .
cd ../..