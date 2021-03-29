#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
 * STRUCT
 * NYÍL OPERÁTOR
 * FÁJLKEZELÉS - ALACSONY SZINT

 * Egy osztály adatainak fájlba írása
 */

struct person {
    unsigned char name[30];
    unsigned char age;
    unsigned int year;
};

//void populate(struct person *s);
void populateArray(struct person *s);

int main() {
    struct person student;
    struct person class[4];
    unsigned char i = 0;

    int dataFile = open("data.txt", O_CREAT | O_RDWR | O_TEXT, S_IREAD | S_IWRITE);

    student.age = 99;
    student.year = 1;
    strcpy(student.name, "Alap Feltoltes");

    populateArray(&class);

    /*while (i < 4) {
        populate(&(class[i]));
        i++;
    }*/

    write(dataFile, &atoi(student.year), &sizeof(atoi(student.year)));
    write(dataFile, &student.nev, sizeof(student.year));
    close(dataFile);
    
    return 0;
}

void populateArray(struct person *s) {
    unsigned char i = 0;
    while (i < 4) {
        printf("\n%d. elem feltöltése\n\n", i);

        printf("Eletkor: ");
        scanf("%d", &((s + i * sizeof(struct person)) -> age));
        printf("\nSzuletesi ev: ");
        scanf("%d", &((s + i * sizeof(struct person)) -> year));

        unsigned char name2[15];
        printf("\nVezeteknev: ");
        scanf("%s", &((s + i * sizeof(struct person)) -> name));
        printf("\nKeresztnev: ");
        scanf("%s", name2);

        strcat(&((s + i * sizeof(struct person)) -> name), " ");
        strcat(&((s + i * sizeof(struct person)) -> name), name2);


        printf("Nev: %s\n", (s + i * sizeof(struct person)) -> name);
        printf("Eletkor: %d\n", (s + i * sizeof(struct person)) -> age);
        printf("Szuletesi ev: %d\n", (s + i * sizeof(struct person)) -> year);

        i++;
    }
    return;
}
/*
void populate(struct person *s) {
    printf("Eletkor: ");
    scanf("%d", &(s -> age));
    printf("\nSzuletesi ev: ");
    scanf("%d", &(s -> year));

    unsigned char name2[15];
    printf("\nVezeteknev: ");
    scanf("%s", &(s -> name));
    printf("\nKeresztnev: ");
    scanf("%s", name2);

    strcat(&(s -> name), " ");
    strcat(&(s -> name), name2);


    printf("Nev: %s\n", s -> name);
    printf("Eletkor: %d\n", s -> age);
    printf("Szuletesi ev: %d\n", s -> year);

    return;
}*/