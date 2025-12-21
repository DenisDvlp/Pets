cmake_minimum_required(VERSION 3.25)

project(display_simulator LANGUAGES CXX RC)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE MAIN_SOURCES
    ${PROJECT_SOURCE_DIR}/../src/*.cpp
    ${PROJECT_SOURCE_DIR}/../src/*.hpp
)
list(REMOVE_ITEM MAIN_SOURCES
    ${PROJECT_SOURCE_DIR}/../src/main.cpp
)

file(GLOB_RECURSE LOCAL_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/*.hpp
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.rc
)
add_executable(${CMAKE_PROJECT_NAME} WIN32
    ${MAIN_SOURCES}
    ${LOCAL_SOURCES}
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../src
)
