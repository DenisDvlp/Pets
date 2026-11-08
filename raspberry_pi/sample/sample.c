#include <stdio.h>
#include "pico/stdlib.h"

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
