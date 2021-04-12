#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    //! BUBBLE SORT

    int szamok[10], i, j, tmp, csere = 0;

    for (i = 0; i < 10; i++) { //! Feltölt
        szamok[i] = rand() % 10;
        printf("%d ", szamok[i]);
    }

    printf("\n\n");

    for (i = 0; i < 9; i++) { //! Loop annyiszor ahány szám van
    csere = 0;
        for (j = 0; j < (9 - i); j++) { //! Loop minden számra hogy kell-e csere
        //? Javítás: mindig egyre kevesebben kell loopolni (a vége jó)
            if (szamok[j] > szamok[j+1]) { //! Csere
                tmp = szamok[j];
                szamok[j] = szamok[j+1];
                szamok[j+1] = tmp;
                csere = 1;
            }
        }
        if (!csere) break;
    }

    for (i = 0; i < 10; i++) {
        printf("%d ", szamok[i]);
    }

    return 0;
}