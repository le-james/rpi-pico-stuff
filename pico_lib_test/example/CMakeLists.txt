add_executable(testLib test.c)

target_link_libraries(testLib PRIVATE pico_stdlib helloLib)

pico_add_extra_outputs(testLib)

pico_enable_stdio_usb(testLib 1)
pico_enable_stdio_uart(testLib 0)