#include <stdio.h>          //printf
#include "pico/stdlib.h"
// #include "hardware/gpio.h"

int main() {
    const uint trig_pin = 16;
    const uint echo_pin = 17;

    // speed of sound
    // const uint v_sound = 343;
    const uint v_sound = 34300;

    // Initialize pins
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);   // onboard led

    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);   // sent signal to sensor

    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);    // receive signal from sensor
    gpio_set_pulls(echo_pin,0,1);       // set pulldown true - returns nothing
    // gpio_pull_up(trig_pin);          // returns a bool

    // Initialize chosen serial port - usb
    stdio_init_all();

    while (true) {
        // send pulses out
        gpio_put(trig_pin,0);   // ensure low first
        sleep_us(1);
        gpio_put(trig_pin,1);
        sleep_us(10);
        gpio_put(trig_pin,0);

        // printf("Pulled down? %d\n",gpio_is_pulled_down(echo_pin));   // check if pin is pulled down
        // printf("gpio status? %d\n",gpio_get(echo_pin));     // check pin high or low

        // do nothing while wait for echo bounce back
        while (gpio_get(echo_pin) == 0) { 
            tight_loop_contents();
            // printf("hear nothin\n");
        }

        // start time once the first pulse comes back
        absolute_time_t start_time = get_absolute_time();

        // receiving pulses back
        while (gpio_get(echo_pin) == 1) {
            tight_loop_contents();
            // sleep_us(1);
        }

        // end time once no pulses comes back or timeout
        absolute_time_t end_time = get_absolute_time();
    
        // compute the round trip time
        uint dt = absolute_time_diff_us(start_time, end_time);

        // printf("dt in mircosec %i\n",dt);

        // compute distance
        float dist = dt * 1e-6 * v_sound / 2;
        printf("Distance [cm]: %f\n", dist);

        sleep_ms(1000);
    }
}

