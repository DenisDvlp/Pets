echo off

: Build the project
if exist build/build.ninja (
    cd build
    ninja
    billiards.exe
) else (
    exit 1
)
