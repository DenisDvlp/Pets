cmake_minimum_required(VERSION 3.25)

# Set the project name and version
project(billiards VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
file(GLOB_RECURSE CPP_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
list(FILTER CPP_FILES EXCLUDE REGEX ".*/build/.*")
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${CPP_FILES})

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
