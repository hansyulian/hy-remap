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
    src/action_macro.cpp
    src/action_profile_shift.cpp
    src/action_simple.cpp
    src/config_loader.cpp
    src/handle_input.cpp
    src/hook_manager.cpp
    src/key_code_map.cpp
    src/keyboard_hook.cpp
    src/main.cpp
    src/mouse_hook.cpp
    src/perform_action.cpp
    src/profile_management.cpp
    src/release_action.cpp
    src/serialize_config.cpp
    src/util_action.cpp
    src/util_input.cpp
    src/util_profile.cpp
    src/util_trigger.cpp
    src/util_window.cpp
)

# Add the executable
add_executable(HRemap ${SOURCES})

# Optionally, if you're using pthreads on Linux or macOS:
# target_link_libraries(HRemap pthread)
