
# Pico 2 W

## Specs

- CPU: RP2350, 150 MHz, Dual-core Arm Cortex-M33 and Hazard3 RISC-V processor.
- On-chip cache: 16 Kb
- SRAM: 520 kb
- Flash memory: 4 Mb
- Bluetooth 5.2 (LE, Classic)
- WiFI 4 (802.11n, 2.4 GHz)
- 3 PIO blocks (12 state machines)
- 26 multi-function GPIO pins

## Types

- ptr: 4
- char: 1
- int: 4
- long: 4
- long long: 8
- float: 4
- double: 8
- long double: 8

## Tips

- To build the project and flash the binary Hold down the `BOOTSEL` button and reset the board. Press `Run project` button in the sidebar of the extension.
- Use serial port rate 115200 bps in Serial Monitor tab to see the logs.
- LED is connected to `CYW43_WL_GPIO_LED_PIN`.
See https://github.com/raspberrypi/pico-examples/blob/master/pico_w/wifi/blink/picow_blink.c
