add_executable(i2c_scanner scanner.c)

# pull in common dependencies
target_link_libraries(i2c_scanner pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(i2c_scanner)

# enable usb output, disable uart output
pico_enable_stdio_usb(i2c_scanner 1)
pico_enable_stdio_uart(i2c_scanner 0)