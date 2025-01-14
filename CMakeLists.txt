cmake_minimum_required(VERSION 3.15)
project(HyRemap)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    src/actions/audio_mixer.cpp
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
# Add your executable (replace main.cpp with your source file)
add_executable(${PROJECT_NAME} ${SOURCES})

# Link nlohmann_json to your target
# Find and include Conan-generated configuration
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json) 

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Enable optimizations
    set(CMAKE_CXX_FLAGS_RELEASE "-lole32 -loleaut32 -lpsapi -O3 -DNDEBUG  -mwindows")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Enable debugging symbols
    set(CMAKE_CXX_FLAGS_DEBUG "-lole32 -loleaut32 -lpsapi -g -O0")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(HyRemap PRIVATE DEBUG_BUILD=1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(HyRemap PRIVATE RELEASE_BUILD=1)
endif()