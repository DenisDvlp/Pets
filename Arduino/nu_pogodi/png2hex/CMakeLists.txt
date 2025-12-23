cmake_minimum_required(VERSION 3.25)

project(png2hex LANGUAGES CXX RC)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ZLIB_BUILD_STATIC ON)
set(ZLIB_BUILD_SHARED OFF)
set(ZLIB_BUILD_TESTING OFF)
set(ZLIB_BUILD_MINIZIP OFF)
set(ZLIB_INSTALL OFF)
add_subdirectory(ext/zlib)

set(PNG_SHARED OFF)
set(PNG_TESTS OFF)
set(PNG_EXECUTABLES OFF)
set(PNG_TOOLS OFF)
add_subdirectory(ext/libpng)

file(GLOB LOCAL_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/*.hpp
)
message(STATUS "Local sources: ${LOCAL_SOURCES}")
add_executable(${CMAKE_PROJECT_NAME}
    ${MAIN_SOURCES}
    ${LOCAL_SOURCES}
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../src
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    zlibstatic
    png_static
)
