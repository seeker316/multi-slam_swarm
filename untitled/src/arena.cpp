#include "display.h"
#include "arena.h"

int main()
{   
    // if(!test()) return -1;

    // arena octag("octagon",8,5,0);
    arena test("circle",3,5,0);
    int i = disp_init(test);

    return 0;
}