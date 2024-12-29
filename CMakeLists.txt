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
    src/keyboar_hook.cpp
    src/mouse_hook.cpp
    src/serialize_config.cpp
    src/actions.cpp
    src/hook_manager.cpp
    src/profile_management.cpp
)

# Add the executable
add_executable(HRemap ${SOURCES})
