#include <cstdio>

class PicoClass
{
    public:
        int x = 5;
};

int main()
{
    PicoClass pico_obj;
    printf("class member variable value %d",pico_obj.x);
}