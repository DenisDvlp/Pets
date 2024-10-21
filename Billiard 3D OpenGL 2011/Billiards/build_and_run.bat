echo off

if exist build/build.ninja (
    cd build
    ninja
    start billiards.exe
)
