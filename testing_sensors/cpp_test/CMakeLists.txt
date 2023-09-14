add_executable(maincppExe main.cpp)

# create map/bin/hex file etc.
pico_add_extra_outputs(maincppExe)

# enable usb output, disable uart output
pico_enable_stdio_usb(maincppExe 1)
pico_enable_stdio_uart(maincppExe 0)