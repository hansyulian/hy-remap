cmake_minimum_required(VERSION 3.10)

# Project name
project(HRemap)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/configuration.cpp
    src/key_hook.cpp
    src/actions.cpp
)

# Add the executable
add_executable(HRemap ${SOURCES})
