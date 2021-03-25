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

void populate(struct person *s);

int main() {
    struct person student;
    struct person class[4];
    unsigned char i = 0;

    int dataFile = open("data.txt", O_CREAT | O_RDWR | O_TEXT, S_IREAD | S_IWRITE);

    student.age = 99;
    student.year = 1;
    strcpy(student.name, "Alap Feltoltes");

    while (i < 4) {
        populate(&(class[i]));
        i++;
    }

    write(dataFile, &atoi(student.year), &sizeof(atoi(student.year)));
    write(dataFile, &student.nev, sizeof(student.year));
    close(dataFile);
    
    return 0;
}

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
}