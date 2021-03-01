#include <stdlib.h>
#include <stdio.h>

void feltolt(unsigned char *szoveg);

int main()
{
    unsigned char szoveg[30] = {};
    feltolt(szoveg);
    return 0;
}

//Átkonvertálás kisbetűkké, csak betűk bekérése
void feltolt(unsigned char *szoveg)
{
    unsigned char c = 0, index = 0;
    while (1)
    {
        c = getche();
        //Ha enter, termináljuk a stringet
        if (c == 13)
        {
            *(szoveg + index) = 0;
            break;
        }
        //Backspace
        if (c == 8 && index > 0)
            *(szoveg + (index--)) = 0;
        //Ha nem betű, újat kérünk be
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
            continue;
        //Mentjük a karaktert
        *(szoveg + index) = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;

        index++;

        if (index == 29)
        {
            *(szoveg + index) = 0;
            break;
        }
    }

    printf("\nbekerve: %s\n%c", szoveg, 7);

    return;
}