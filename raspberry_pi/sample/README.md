
# Pico 2 W

## Specs

- CPU: RP2350, 150 MHz, Dual-core
- On-chip cache: 16 Kb
- SRAM: 520 kb
- Flash memory: 4 Mb
- Bluetooth 5.2 (LE, Classic)
- WiFI 4 (802.11n, 2.4 GHz)
- 3 PIO blocks (12 state machines)

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

- Serial port rate: 115200 bps.
- LED is connected to `CYW43_WL_GPIO_LED_PIN`.
See https://github.com/raspberrypi/pico-examples/blob/master/pico_w/wifi/blink/picow_blink.c
