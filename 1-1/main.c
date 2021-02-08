#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a = -2; //-128..127
    unsigned char b; //0..255
    int c = 1234;

    a = c;
    //c = a;
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("a = %x, b = %x, c = %x", a, b, c);
    
    return 0;
}