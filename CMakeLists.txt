# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(HyRemap VERSION 1.0)
set(CMAKE_CXX_COMPILER "g++.exe")
set(CMAKE_C_COMPILER "gcc.exe")
# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Default to Release build if no build type is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set additional flags for different build types
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Enable optimizations
    set(CMAKE_CXX_FLAGS_RELEASE "-lole32 -loleaut32 -lpsapi -O3 -DNDEBUG  -mwindows")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Enable debugging symbols
    set(CMAKE_CXX_FLAGS_DEBUG "-lole32 -loleaut32 -lpsapi -g -O0")
endif()

# Add source files
set(SOURCES
    src/main.cpp
    src/config/config_loader.cpp
    src/config/debug_config.cpp
    src/config/optimized_config.cpp
    src/config/json_serializer.cpp
    src/config/key_code_map.cpp
    src/actions/macro.cpp
    src/actions/profile_shift.cpp
    src/actions/simple.cpp
    src/actions/run_program.cpp
    src/controllers/input_remapping.cpp
    src/controllers/hook_manager.cpp
    src/controllers/keyboard_hook.cpp
    src/controllers/mouse_hook.cpp
    src/controllers/perform_action.cpp
    src/controllers/profile_management.cpp
    src/controllers/release_action.cpp
    src/modules/audio_mixer_control.cpp
    src/utils/action.cpp
    src/utils/input.cpp
    src/utils/profile.cpp
    src/utils/trigger.cpp
    src/utils/window.cpp
    src/utils/string.cpp
    src/utils/run_program.cpp
    src/utils/key_code.cpp
)

# Add include directories (if any)
include_directories(
    ${PROJECT_SOURCE_DIR}/include  # Include the headers directory if needed
)

# Add the executable
add_executable(HyRemap ${SOURCES})

# Set platform-specific configurations if necessary
if(MINGW)
    # If we're using MinGW, you can set specific flags or configurations here
    message(STATUS "Building for MinGW")
elseif(WIN32)
    # Handle other Windows-specific configurations
    message(STATUS "Building for Windows")
endif()

# Optionally, set up installation targets for cross-platform deployment (uncomment if needed)
# install(TARGETS HyRemap DESTINATION bin)

# Add preprocessor definitions after the target is created
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(HyRemap PRIVATE DEBUG_BUILD=1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(HyRemap PRIVATE RELEASE_BUILD=1)
endif()