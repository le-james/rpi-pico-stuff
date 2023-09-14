#include <stdio.h>
#include "pico/stdlib.h"

void print_mesg();

int main_imu();

int main() {

    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true) {

        // Blink LED
        // printf("Blinking!\r\n");

        // print_mesg();

        main_imu();
        
        // doesnt blink if using main_imu()
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
}