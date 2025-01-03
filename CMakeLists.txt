cmake_minimum_required(VERSION 3.10)

# Project name
project(HRemap)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add additional include directories (for nlohmann, which is header-only)
include_directories(${CMAKE_SOURCE_DIR}/include/nlohmann)

# Source files
set(SOURCES
    src/main.cpp
    src/config/config_loader.cpp
    src/config/debug_config.cpp
    src/config/optimized_config.cpp
    src/config/serialize_config.cpp
    src/actions/macro.cpp
    src/actions/profile_shift.cpp
    src/actions/simple.cpp
    src/modules/handle_input.cpp
    src/modules/hook_manager.cpp
    src/modules/key_code_map.cpp
    src/modules/keyboard_hook.cpp
    src/modules/mouse_hook.cpp
    src/modules/perform_action.cpp
    src/modules/profile_management.cpp
    src/modules/release_action.cpp
    src/utils/action.cpp
    src/utils/input.cpp
    src/utils/profile.cpp
    src/utils/trigger.cpp
    src/utils/window.cpp
    src/utils/string.cpp
)

# Add the executable
add_executable(HRemap ${SOURCES})

# Optionally, if you're using pthreads on Linux or macOS:
# target_link_libraries(HRemap pthread)
