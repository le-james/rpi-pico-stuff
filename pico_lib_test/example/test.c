#include "hello.h"
#include "pico/stdlib.h"

int main() {

    stdio_init_all();

    while (1)
    {
        hello_world();
        sleep_ms(1000);
    }

}