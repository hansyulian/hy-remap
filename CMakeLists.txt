cmake_minimum_required(VERSION 3.15)
project(HyRemap)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
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
    src/utils/instance.cpp
    src/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Use Conan package for nlohmann_json
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Add system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ole32 oleaut32 psapi)

# Set build-specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Define macro and enable optimizations
    target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD=1)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -DNDEBUG)
    
    # 🔒 Static linking of standard libs to avoid DLL issues
    target_link_options(${PROJECT_NAME} PRIVATE -static-libstdc++ -static-libgcc -mwindows)

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD=1)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
endif()
