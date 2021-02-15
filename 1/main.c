#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a = -2; //-128..127
    unsigned char b; //0..255
    int c = 1234;
    unsigned char e = 2, f = 3, g = 123, h = 15, i = 47;
    unsigned char j[100];

    a = c;
    /* c = a;
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("a = %x, b = %x, c = %x", a, b, c);
    */
    b = ~(e & f); //bitwise
    printf("b = %d\n", b);
    b = !(e && f); //logical
    printf("b = %d\n\n", b);

    a = (e > f) ? e : f; //összevont logika
    printf("a = %d\n\n", a);

    /*FELADAT: float vs. double, 100 értéket összeadva melyik pontosabb?*/

    /*FELADAT: Összevont logikával e, f, g, h, i közül legnagyobb?*/

    /*FELADAT: Terem. 8 darab világító test (8 bit)
    Ezeket a lámpákat külön-külön véletlenszerűen bekapcsolva 100 esetben.
    Ezeket vizsgálva az egyes bitek hány esetben voltak bekapcsolva?
    RANDOM: rand()*/

    return 0;
}