echo off

rm -rf build
mkdir build
cd build

: Generate build files
cmake -GNinja .. && (
    set cmakeResult=1
) || (
    set cmakeResult=0
)

: Build the project
if %cmakeResult% == 1 (
    ninja
    start billiards.exe
)
