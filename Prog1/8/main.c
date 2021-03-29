#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* MAGASSZINTŰ FÁJLKEZELÉS
! 
! Különbség: Nem közvetlenül írunk, hanem egy bufferbe, amit utána lezárunk.

    * MEGNYITÁS
    * fopen: FILE(azonosító, bufferméret, fájlattribútumok)
    * w - írás
    * w+ - olvasás
    * w+t - text mode
    
    * OLVASÁS
    * fread - bájtonként
    * getc
    * gets
    * fscanf - formátumozott
    
    * ÍRÁS
    * fwrite - bájtonként
    * fputc
    * fputs
    * fprintf - formátumozott
    
    * POZÍCIONÁLÁS
    * fseek
    
    * LEZÁRÁS
*/

int main() {
    //? 1. FELADAT: String kiírása majd visszaolvasása

    struct szemely
    {
        unsigned char nev[30];
        unsigned char eletkor;
        int szulev;
    };

    struct szemely szemely_adat;    

    FILE *fp;
    fp = fopen("adatok.txt", "w+t");
    if (fp == NULL) {
        printf("Fajlmegnyitas nem sikerult!");
        return 1;
    }

    //unsigned char i = 0;
    //while (i < 3) {
        scanf("%s", szemely_adat.nev);
        scanf("%d", &szemely_adat.eletkor);
        scanf("%d", &szemely_adat.szulev);
       // i++;
    //}

    unsigned char szoveg[10] = "Proba 1234";
    unsigned char szoveg1[10] = {0};
    
    //fwrite(&szemely_adat, sizeof(szemely_adat), 1, fp);
    fprintf(fp, "%s %d %d", szemely_adat.nev, szemely_adat.eletkor, szemely_adat.szulev);

    fflush(fp);
    fseek(fp, 0, SEEK_SET); //!0-val arrébb a SEEK_SET-hez képest

    struct szemely szemely_adat1;

    //fread(&szemely_adat, sizeof(szemely_adat), 1, fp);
    fscanf(fp, "%s %d %d", szemely_adat1.nev, &szemely_adat1.eletkor, &szemely_adat1.szulev);

    printf("\nVisszaolvasott nev: %s", szemely_adat1.nev);
    printf("\nVisszaolvasott eletkor: %d", szemely_adat1.eletkor);
    printf("\nVisszaolvasott szuletesi ev: %d", szemely_adat1.szulev);

    fclose(fp);

    return 0;
}