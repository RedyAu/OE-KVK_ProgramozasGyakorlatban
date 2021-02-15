#include <stdio.h>
#include <stdlib.h>

unsigned char getParity(unsigned char num);
unsigned char getDigitParityQuantity(int a, int b);
int getLampsSwitched(unsigned char *lamps);

int main()
{
  { //1. feladat | 2-vel oszthatóság
    unsigned char a = 3, b, c, d;

    b = (a % 2 == 0) ? 0 : 1;
    c = a & 1;

    d = getParity(a);

    printf("1. b = %d, c = %d, d = %d\n", b, c, d);
  }
  { //2. feladat | 4-gyel oszthatóság
    unsigned char a = 16, b, c;
    b = (a % 4 == 0) ? 0 : 1;
    c = a & 3; //0000 0011

    printf("2. b = %d, c = %d\n", b, c);
  }
  { //3. feladat | Darabszám
    int a = 2, b = 0, c;
    c = getDigitParityQuantity(a, b);
    printf("3. c = %d\n", c);
  }
  { //4. feladat | Lámpák
    printf("4.\n");
    unsigned char lamps[100];
    int a;
    a = getLampsSwitched(lamps);
  }
  return 0;
}

// 1. feladat kiegészítés
unsigned char getParity(unsigned char num)
{
  return num & 1;
}

//3. feladat kiegészítés
//A két számban hány páros számjegy van?
unsigned char getDigitParityQuantity(int a, int b)
{
  //1-esek helyiértéke: Mod 10
  return !(a & 1) + !(a / 10 & 1) + !(a / 100 & 1) + !(b & 1) + !(b / 10 & 1) + !(b / 100 & 1);
}

//4. feladat kiegészítés
int getLampsSwitched(unsigned char *lamps)
{
  int i = 0;
  while (i < 100) {
    lamps[i] = rand() % 256;
    printf("%d ", lamps[i]);
    i++;
  }
  return 0;
}