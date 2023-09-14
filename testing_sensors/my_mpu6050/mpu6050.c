#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"



#define PIN_SDA 4
#define PIN_SCL 5

// mpu6050 address
static const uint8_t MPU6050_ADDR = 0X68;

// register with imu id (address)
static const uint8_t WHO_AM_I = 0X75;

// accelerometer config address pg 15
static const uint8_t ACCEL_CONFIG = 0X1C;



int main() {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    // This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL) running at 400kHz
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);

    // Ports
    i2c_inst_t * i2c = i2c0;

    // Buffer to store id
    uint8_t id[1];

    //  reset
    // uint8_t buf[] = {0x6B, 0x00};
    // i2c_write_blocking(i2c, MPU6050_ADDR, buf, 2, false);

    // led for check
    gpio_put(25, true);
    // &WHO_AM_I points to a location where 0X75 is stored
    int written = i2c_write_blocking(i2c,MPU6050_ADDR,&WHO_AM_I,1,true);
    gpio_put(25, false);

    // arrays are pointers
    int read_id = i2c_read_blocking(i2c,MPU6050_ADDR,id,1,false);

    // accelerometer config 
    // uint8_t data[2];
    // data[0] = ACCEL_CONFIG;
    // data[1] = 0x18;                                     // config for +-8g
    // i2c_write_blocking(i2c,MPU6050_ADDR,data,2,true);

    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x00};
    // uint8_t buf = 0x6B;
    // uint8_t buf[] = {0x6B, 0x80};
    i2c_write_blocking(i2c0, MPU6050_ADDR, buf, 2, false);

    while(true) {

        uint8_t accel[6];

        // Start reading acceleration registers from register 0x3B for 6 bytes
        uint8_t val = 0x3B;
        i2c_write_blocking(i2c0, MPU6050_ADDR, &val, 1, true); // true to keep master control of bus
        i2c_read_blocking(i2c0, MPU6050_ADDR, accel, 6, false);

        // for (int i = 0; i < 3; i++) {
        //     accel[i] = (accel[i * 2] << 8 | accel[(i * 2) + 1]);
        // }

        printf("raw accel values: ");
        printf("Ax: %d   ",accel[0] << 8 | accel[1]);
        printf("Ay: %d   ",accel[2] << 8 | accel[3]);
        printf("Az: %d\n",accel[4] << 8 | accel[5]);

        printf("m/s^s accel values: ");
        printf("Ax: %f   ",(accel[0] << 8 | accel[1])*(1.0/16384)*9.807 );
        printf("Ay: %f   ",(accel[2] << 8 | accel[3])*(1.0/16384)*9.807 );
        printf("Az: %f\n",(accel[4] << 8 | accel[5])*(1.0/16384)*9.807 );

        sleep_ms(1000);


        // // check bytes
        // printf("Number of bytes written: %d\n",written);   
        // printf("Number of bytes read: %d\n",read_id);

        // // check imu id (address)
        // printf("Device ID (hex): %d\n",id[0]);
        // if(id[0] == MPU6050_ADDR){
        //     printf("ID matches!\n");
        // }
        // sleep_ms(1000);

        // printf("hello\n");
    }
}










// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/i2c.h"

// // I2C address
// static const uint8_t MPU6050_ADDR = 0X68;

// // Registers
// static const uint8_t WHO_AM_I = 0X75;

// /*******************************************************************************
//  * Function Declarations
//  */
// int reg_write(i2c_inst_t *i2c, 
//                 const uint addr, 
//                 const uint8_t reg, 
//                 uint8_t *buf,
//                 const uint8_t nbytes);

// int reg_read(   i2c_inst_t *i2c,
//                 const uint addr,
//                 const uint8_t reg,
//                 uint8_t *buf,
//                 const uint8_t nbytes);

// /*******************************************************************************
//  * Function Definitions
//  */

// // Write 1 byte to the specified register
// int reg_write(  i2c_inst_t *i2c, 
//                 const uint addr, 
//                 const uint8_t reg, 
//                 uint8_t *buf,
//                 const uint8_t nbytes) {

//     int num_bytes_read = 0;
//     uint8_t msg[nbytes + 1];

//     // Check to make sure caller is sending 1 or more bytes
//     if (nbytes < 1) {
//         return 0;
//     }

//     // Append register address to front of data packet
//     msg[0] = reg;
//     for (int i = 0; i < nbytes; i++) {
//         msg[i + 1] = buf[i];
//     }

//     // Write data to register(s) over I2C
//     i2c_write_blocking(i2c, addr, msg, (nbytes + 1), false);

//     return num_bytes_read;
// }

// // Read byte(s) from specified register. If nbytes > 1, read from consecutive
// // registers.
// int reg_read(  i2c_inst_t *i2c,
//                 const uint addr,
//                 const uint8_t reg,
//                 uint8_t *buf,
//                 const uint8_t nbytes) {

//     int num_bytes_read = 0;

//     // Check to make sure caller is asking for 1 or more bytes
//     if (nbytes < 1) {
//         return 0;
//     }

//     // Read data from register(s) over I2C
//     i2c_write_blocking(i2c, addr, &reg, 1, true);
//     num_bytes_read = i2c_read_blocking(i2c, addr, buf, nbytes, false);

//     return num_bytes_read;
// }

// /*******************************************************************************
//  * Main
//  */
// int main() {

//     gpio_init(25);
//     gpio_set_dir(25, GPIO_OUT);

//     // Pins
//     const uint sda_pin = 6;
//     const uint scl_pin = 7;

//     // Ports
//     i2c_inst_t *i2c = i2c0;

//     // Buffer to store raw reads
//     uint8_t data[1];

//     // Initialize chosen serial port
//     stdio_init_all();

//     //Initialize I2C port at 400 kHz
//     i2c_init(i2c, 400 * 1000);

//     // Initialize I2C pins
//     gpio_set_function(sda_pin, GPIO_FUNC_I2C);
//     gpio_set_function(scl_pin, GPIO_FUNC_I2C);

//     gpio_put(25, true);

//     // Read device ID to make sure that we can communicate with the IMU
//     reg_read(i2c, MPU6050_ADDR, WHO_AM_I, data, 1);

//     gpio_put(25, false);

//     // Loop forever
//     while (true) {

//         printf("id of device: %x",data[0]);

//         sleep_ms(1000);
//     }
// }
