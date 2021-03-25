#include <stdio.h>
#include <stdlib.h>

void greet();
void readNumber(unsigned char *);
void readSign();
void getSolution(unsigned char *first, unsigned char *second, int *solution);
void printSolution(int solution);

int main()
{ //Számológép program
    while (1)
    {
        //szambekeres
        //muvelet
        //szambekeres
        //szamolas
        //ism
        unsigned char first, second;
        int solution;

        greet();
        readNumber(&first);
        readSign();
        readNumber(&second);
        getSolution(&first, &second, &solution);
        printSolution(solution);
    }
    return 0;
}

void greet()
{
    printf("Hello");
}

void readNumber(unsigned char *num)
{
    //scanf("%d", num); //scanf: mindig a helyét kell megadni
    //scanf rossz! a memóriában továbbír ha hosszabb az adat

    /*HÁZI FELADATOK:

    - bekérő karakteres típusra
    - bekérő integeres típusra
    - bekérő double típusra
    - bekérő string típusra
    */
    unsigned char c;
    *num = 0;
    while (1)
    {
        do
        {
            c = getch();
        } while (c < '0' || c > '9' || c != '\n');
        if (c == 13)
            break; //enter -> 13
        *num = *num+c-'0';
    }
}

void readSign()
{
}

void getSolution(unsigned char *first, unsigned char *second, int *solution)
{
}

void printSolution(int solution)
{
}