#include <stdio.h>
#include "pico/stdlib.h"

// CPU: RP2350, 150 MHz, Dual-core
// On-chip cache: 16 Kb
// SRAM: 520 kb
// Flash memory: 4 Mb
// Bluetooth 5.2 (LE, Classic)
// WiFI 4 (802.11n, 2.4 GHz)
// 3 PIO blocks (12 state machines)
//
// Types:
// - ptr: 4
// - char: 1
// - int: 4
// - long: 4
// - long long: 8
// - float: 4
// - double: 8
// - long double: 8

int main()
{
    stdio_init_all();

    while (true) {
        printf("Size ptr: %zu\n", sizeof(int *));
        printf("Size int: %zu\n", sizeof(int));
        printf("Size char: %zu\n", sizeof(char));
        printf("Size float: %zu\n", sizeof(float));
        printf("Size double: %zu\n", sizeof(double));
        printf("Size long: %zu\n", sizeof(long));
        printf("Size long long: %zu\n", sizeof(long long));
        printf("Size long double: %zu\n", sizeof(long double));
        sleep_ms(1000);
    }
}
