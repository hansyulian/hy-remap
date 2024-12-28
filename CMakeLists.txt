cmake_minimum_required(VERSION 3.10)  # Specify CMake version

# Project name
project(HRemap)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)
# Add the executable and link the source files
add_executable(HRemap main.cpp)
