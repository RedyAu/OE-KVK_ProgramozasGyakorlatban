#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c %c %c %c"
#define BYTE_TO_BINARY(byte)     \
  (byte & 0x80 ? '1' : '0'),     \
      (byte & 0x40 ? '1' : '0'), \
      (byte & 0x20 ? '1' : '0'), \
      (byte & 0x10 ? '1' : '0'), \
      (byte & 0x08 ? '1' : '0'), \
      (byte & 0x04 ? '1' : '0'), \
      (byte & 0x02 ? '1' : '0'), \
      (byte & 0x01 ? '1' : '0')

#define SwitchCount 100

void nothing();

int main()
{
  srand(time(NULL)); //Ha nincs ez a sor, a random mindig ugyanazokat az értékeket adja.
  {                  //1. feladat | Lámpák
    printf("1. feladat\n");
    unsigned char lamps[SwitchCount];
    unsigned char lampsSwitched[] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (unsigned char i = 0; i < SwitchCount; i++)
      lamps[i] = rand();

    for (unsigned char i = 0; i < 8; i++)
    {
      unsigned char prev = lamps[0] & (0x01 << i);

      for (unsigned char j = 0; j < SwitchCount; j++)
      {
        unsigned char maskedBit = lamps[j] & (0x01 << i);
        if (prev != maskedBit)
          lampsSwitched[i]++;
        prev = maskedBit;
      }
    }

    for (unsigned char i = 7; i < 8; i--)
    {
      printf("%d ", lampsSwitched[i]);
    }
  }
  { //2. feladat
    int a = 12, b = 3, c = 5, d = 8, e = 10, min;
    min = (a < b)
              ? (
                    (a < c)
                        ? (
                              (a < d)
                                  ? (
                                        (a < e)
                                            ? a
                                            : e)
                                  : (
                                        (d < e)
                                            ? d
                                            : e))
                        : (
                              (c < d)
                                  ? (
                                        (c < e)
                                            ? c
                                            : e)
                                  : (
                                        (d < e)
                                            ? d
                                            : e)))
              : (
                    (b < c)
                        ? (
                              (b < d)
                                  ? (
                                        (b < e)
                                            ? b
                                            : e)
                                  : (
                                        (d < e)
                                            ? d
                                            : e))
                        : (
                              (c < d)
                                  ? (
                                        (c < e)
                                            ? c
                                            : e)
                                  : (
                                        (d < e)
                                            ? d
                                            : e)));
    printf("\n\n2. feladat\nmin: %d", min);
  }
  { //2. feladat
    int a = 12, b = 3, c = 5, d = 8, e = 10, max;
    max = (a > b)
              ? (
                    (a > c)
                        ? (
                              (a > d)
                                  ? (
                                        (a > e)
                                            ? a
                                            : e)
                                  : (
                                        (d > e)
                                            ? d
                                            : e))
                        : (
                              (c > d)
                                  ? (
                                        (c > e)
                                            ? c
                                            : e)
                                  : (
                                        (d > e)
                                            ? d
                                            : e)))
              : (
                    (b > c)
                        ? (
                              (b > d)
                                  ? (
                                        (b > e)
                                            ? b
                                            : e)
                                  : (
                                        (d > e)
                                            ? d
                                            : e))
                        : (
                              (c > d)
                                  ? (
                                        (c > e)
                                            ? c
                                            : e)
                                  : (
                                        (d > e)
                                            ? d
                                            : e)));
    printf("\n\n3. feladat\nmax: %d", max);
  }
  {
    int a = 12, b = 3, c = 5, d = 8, e = 10, paros = 0;
    paros += (a & 1) ? 0 : a;
    paros += (b & 1) ? 0 : b;
    paros += (c & 1) ? 0 : c;
    paros += (d & 1) ? 0 : d;
    paros += (e & 1) ? 0 : e;
    
    printf("\n\n4. feladat\nparos: %d", paros);
  }
  {
    int a = 12, b = 3, c = 5, d = 8, e = 10, paratlan = 0;
    paratlan += (a & 1) ? a : 0;
    paratlan += (b & 1) ? b : 0;
    paratlan += (c & 1) ? c : 0;
    paratlan += (d & 1) ? d : 0;
    paratlan += (e & 1) ? e : 0;
    
    printf("\n\n5. feladat\nparatlan: %d", paratlan);
  }
  {
    int a = 12, b = 3, c = 5, d = 8, e = 10, paros = 0;
    paros ^ (a & 1) ? 0 : a;
    paros ^ (b & 1) ? 0 : b;
    paros ^ (c & 1) ? 0 : c;
    paros ^ (d & 1) ? 0 : d;
    paros ^ (e & 1) ? 0 : e;
    
    printf("\n\n6. feladat\nparos: %d", paros);
  }
  return 0;
}

void nothing() {
  return;
}