cmake_minimum_required(VERSION 3.25)

# Pre-checks
if (NOT WIN32)
    message(FATAL_ERROR "The project is designed for Windows OS.")
endif()

# Set the project name and version
project(Billiards VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Additional general settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(utils)

# Copliler options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS -fdiagnostics-color=always)

# Add the executable
file(GLOB_RECURSE CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${CPP_FILES})

# preprocessor definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE UNICODE)

# Find OpenGL package
include(FindOpenGL)

# Include the OpenGL headers
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/inc"
)

# Link the OpenGL library and necessary Windows libraries
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    ${OPENGL_LIBRARIES}
)

# Diagnostics
get_target_compiler_flags(${CMAKE_PROJECT_NAME} COMPILER_FLAGS)
message("COMPILER_FLAGS:${COMPILER_FLAGS}")