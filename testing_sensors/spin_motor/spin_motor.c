#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"

#include "hardware/adc.h"
// #include "hardware/gpio.h"   // not needed
#include "hardware/pwm.h"

// double sigmoid(double n) {
//     return (1 / (1 + pow(2.71828, -n)));
// }

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    const uint pwm_pin = 15;


    // Tell GPIO 15 it is allocated to the PWM
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 15
    uint slice_num = pwm_gpio_to_slice_num(pwm_pin);

    // Set the PWM running
    pwm_set_enabled(slice_num, true);

    // Set period of 4 cycles (0 to 3 inclusive)
    // pwm_set_wrap(slice_num, 65535);

    float max_duty = 65465;  // 125MHz/38.1875 <- this is the new frequency of the pwm
    pwm_set_clkdiv_int_frac(slice_num,38,3);

    // float max_duty = 39062;  // 125MHz/64 <- this is the new frequency of the pwm
    // pwm_set_clkdiv_int_frac(slice_num,64,0);

    pwm_set_wrap(slice_num,max_duty);

    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);

    // pot setup
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    // initiate serial
    stdio_init_all();

    while (1) {

        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 6547.0f/((1 << 12)-1);
        uint16_t result = adc_read();
        // printf("Raw value: %d, map val: %f\n", result, round(result * conversion_factor * 100.0)/100.0);
        printf("Raw value: %d, map val: %f\n", result, round(result * conversion_factor));
        // sleep_ms(500);

        // long pot_val = map(result, 0, 4095, 0, 6547);
        // printf("mapped val: %d\n", pot_val);
        // sleep_ms(500);

        // pwm_set_chan_level(slice_num, PWM_CHAN_B, pot_val);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, round(result * conversion_factor));
        // sleep_ms(500);


        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
        // sleep_ms(1000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 2*max_duty/5);
        // sleep_ms(1000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 3*max_duty/5);
        // sleep_ms(1000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 4*max_duty/5);
        // sleep_ms(1000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, max_duty);


        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);     // 50% duty cycle
        // sleep_ms(3000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, max_duty*0.07);     // 50% duty cycle
        // sleep_ms(3000);


        // pwm_set_chan_level(slice_num, PWM_CHAN_B, max_duty);
        // sleep_ms(5000);
        // pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);

        // while (1){
            
        // }
        
    }
}

