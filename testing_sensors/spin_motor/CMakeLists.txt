add_executable(motor spin_motor.c)

# pull in common dependencies
target_link_libraries(motor pico_stdlib hardware_pwm hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(motor)

# enable usb output, disable uart output
pico_enable_stdio_usb(motor 1)
pico_enable_stdio_uart(motor 0)