#include <stdio.h>
#include <stdlib.h>

int tombkezelo(int *tomb);

int main()
{
    { //1: Tömbkezelés
        int tomb[10];
        tombkezelo(tomb);
    }
    return 0;
}

int tombkezelo(int *tombPointer)
{
    int i = 0;
    for (i < 10; i++;)
    {
        *(tombPointer + i) = rand(); // === tombPointer[i] = rand();
        printf("%d\n", *tombPointer);
    }
}