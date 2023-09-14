add_executable(ultra ultra.c)

# pull in common dependencies
target_link_libraries(ultra pico_stdlib)
# target_link_libraries(ultra pico_stdlib hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(ultra)

# enable usb output, disable uart output
pico_enable_stdio_usb(ultra 1)
pico_enable_stdio_uart(ultra 0)