echo off

rm -rf build
mkdir build
cd build

: Generate build files
cmake -GNinja ..

: Build the project
ninja
