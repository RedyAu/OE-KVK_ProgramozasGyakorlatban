//G2NFHW
//Fodor Andras Benedek
//Prog1 Labor ZH
//2021. 04. 26.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first(int start, int end);
int second(int start, int end);
int third(int startA, int endA, int startB, int endB);
int fourth(int num);
int fifth(int num);

int main()
{
    int firstSolution, secondSolution, thirdSolution, fourthSolution, fifthSolution;
    const int start1 = -16200, end1 = -14499;
    const int start2 = -11000, end2 = -1000;
    const int startA3 = 5000, endA3 = 9900, startB3 = 100, endB3 = 7000;
    const int num4 = 4305;
    const int num5 = 5000;

    firstSolution = first(start1, end1);
    printf("\nElso feladat eredmenye: %o", firstSolution); //Oktalis!

    secondSolution = second(start2, end2);
    printf("\nMasodik feladat eredmenye: %X", secondSolution); //Hexa!

    thirdSolution = third(startA3, endA3, startB3, endB3);
    printf("\nHarmadik feladat eredmenye: %d", thirdSolution); //Decimalis!

    fourthSolution = fourth(num4);
    printf("\nNegyedik feladat eredmenye: %d", fourthSolution); //Decimalis!

    fifthSolution = fifth(num5);
    printf("\nNegyedik feladat eredmenye: %d", fifthSolution);

    return 0;
}

int first(int start, int end)
{
    int i, sum = 0;
    for (i = start; i < end; i++)
    {
        if ((i & 0b10000101) == 0b10000100)
            sum += i;
    }
    return sum;
}

int second(int start, int end)
{
    int i, count = 0, y;
    for (i = start; i < end; i++)
    {
        if ((i % 6 == 0) && (i / 10 % 10 == 0))
            count++;
        if (count > 0)
        {
            y++;
        }
    }
    return count;
}
  
int third(int startA, int endA, int startB, int endB)
{
    int count = 0, a, b, bad = 0;
    for (a = startA; a < endA; a += 5)
    {
        bad = 0;
        for (b = startB; b < endB; b += 16)
        {
            if (a == b)
            {
                bad = 1;
                break;
            }
        }
        if (!bad)
        {
            count++;
        }
    }
    return count;
}

int fourth(int num)
{
    int sum = 0, i, prime, primeTemp;

    for (i = 1; i <= num; i++)
    {
        prime = 0;
        for (primeTemp = 1; primeTemp <= i; primeTemp++)
        {
            if ((i % primeTemp) == 0)
                prime++;
        }
        if ((prime == 2) && !(num % i))
            sum += i;
    }
    return sum;
}

int fifth(int num)
{
    int i = 0, prevStar = 0, star, square, solution = 0, tmp = 0;

    while (1)
    {
        square = i * i;
        prevStar = star;
        star = ((6 * square) - (6 * i) + 1);
        if (star > num)
        {
            if ((abs(num - star)) > (abs(num - prevStar)))
            {
                solution = prevStar;
            }
            else
            {
                solution = star;
            }
            break;
        }

        i++;
    }
    return solution;
}
