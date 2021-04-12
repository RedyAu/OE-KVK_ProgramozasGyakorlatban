#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *szamok);
void binSort(int *szam);

int main() {
    //! SORTING

    int szamok[10], i, j, tmp, csere = 0;

    for (i = 0; i < 10; i++) { //! Feltölt
        szamok[i] = rand() % 10;
        printf("%d ", szamok[i]);
    }

    printf("\n\n");

    binSort(szamok);

    for (i = 0; i < 10; i++) {
        printf("%d ", szamok[i]);
    }

    return 0;
}

void binSort(int *a) { //* Kétszer olyan gyors mint a Bubble
    int i, j, b[10] = {0};

    for (i = 0; i < 10; i++) {
        b[a[i]]++; //! B-t feltöltjük az egyes számok gyakoriságával
    }

    //! Legeneráljuk a választ B-ből
    for (i = 0, j = 0; j < 10; j++) {
        for (; b[j] > 0; b[j]--, i++) {
            a[i] = j;
        }
    }
}

void bubbleSort(int *szamok) {
    int i, j, csere = 0, tmp;

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
}