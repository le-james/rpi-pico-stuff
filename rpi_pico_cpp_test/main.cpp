// #include <stdio.h>
#include <cstdio>
#include "pico/stdlib.h"

class PicoClass
{
    public:
        int x = 5;
};

int main()
{
    stdio_init_all();

    PicoClass pico_obj;
    while(true)
    {
        printf("class member variable value: %d \n",pico_obj.x);
        sleep_ms(1000);

    }
}

// int main()
// {
//     stdio_init_all();

//     while(true)
//     {
//         printf("testing testing");
//         sleep_ms(1000);
//     }
// }