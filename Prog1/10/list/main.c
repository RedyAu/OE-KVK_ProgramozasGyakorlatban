#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct itemStruct {
    int ertek;
    struct itemStruct *elozo; //* Tartalmazhatja önmagát
    struct itemStruct *kovetkezo;
} item;

item *elso, *utolso;

void bevitel(void);
void listazas_elore(void);
void listazas_vissza(void);
void torles(int);

int main(void) {
    //! Kétszeresen láncolt lista
    int db = 4;
    elso = NULL;
    utolso = NULL;

    while (db--) {
        bevitel();
        listazas_elore(); 
        listazas_vissza(); 
    }

    torles(15);
    listazas_elore(); 
    listazas_vissza(); 
    
    return 0;
}

void bevitel(void) {
    printf("\n\n\nUj ertek: ");
    item *ujelem, *aktualis;
    aktualis = elso;
    ujelem = malloc(sizeof(item));
    scanf("%d", &(ujelem->ertek));
    if (!elso) { //! ha nullpointer - azaz üres a lista
        ujelem->elozo = NULL;
        ujelem->kovetkezo = NULL;
        elso = ujelem;
        utolso = ujelem;
    } else {
        //! Hely megkeresése
        while (ujelem->ertek > aktualis->ertek && aktualis->kovetkezo) //! Amíg az új nagyobb mint a már meglévők, és nem értünk a lista végére
            aktualis = aktualis->kovetkezo;

        //* Ide már csak az aktuális megfelelő állapotában érünk el
        if (!aktualis->elozo) { //!Ha nem volt előző elem a listában - beszúrás a lista ELEJÉRE
            ujelem->elozo = aktualis->elozo; //* NULL
            ujelem->kovetkezo = aktualis;
            aktualis->elozo = ujelem;
            elso = ujelem;
        } else {
            if (ujelem->ertek < utolso->ertek) { //! KÖZTES érték
                ujelem->elozo = aktualis->elozo;
                ujelem->kovetkezo = aktualis;
                aktualis->elozo->kovetkezo = ujelem;
                aktualis->elozo = ujelem;
            } else { //! VÉGÉRE
                ujelem->elozo = aktualis;
                ujelem->kovetkezo = aktualis->kovetkezo; //* NULL
                aktualis->kovetkezo = ujelem;
                utolso = ujelem;
            }
        }
    }
}

void listazas_elore() {
    item *aktualis;
    aktualis = elso;

    printf("\n\nElore:\n");

    while (aktualis->kovetkezo) {
        printf("%d\t", aktualis->ertek);
        aktualis = aktualis->kovetkezo;
    }
    printf("%d\t", aktualis->ertek);
}

void listazas_vissza() {
    item *aktualis;
    aktualis = utolso;

    printf("\n\nHatra:\n");

    while (aktualis->elozo) {
        printf("%d\t", aktualis->ertek);
        aktualis = aktualis->elozo;
    }
    printf("%d\t", aktualis->ertek);
}

void torles(int del) { //TODO házi
    return;
}