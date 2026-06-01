
:: PICO_BOARD: *.h in sdk\2.2.0\src\boards\include\boards\
:: PICO_PLATFORM: *.cmake in sdk\2.2.0\cmake\preload\platforms\
:: PICO_COMPILER: *.cmake in sdk\2.2.0\cmake\preload\toolchains\

cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release ^
-DPICO_SDK_PATH="%USERPROFILE%\.pico-sdk\sdk\2.2.0" ^
-DPICO_TOOLCHAIN_PATH="%USERPROFILE%\.pico-sdk\toolchain\15_2_Rel1" ^
-Dpicotool_DIR="%USERPROFILE%\.pico-sdk\picotool\2.2.0-a4\picotool" ^
-DPICO_BOARD=pico2_w ^
-DPICO_PLATFORM=rp2350-arm-s ^
-DPICO_COMPILER="pico_arm_cortex_m33_gcc"
