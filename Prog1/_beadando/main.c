#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

//!Set up wide character support on Windows
#include <wchar.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>

static int consoleWide(FILE *stream)
{
    return _setmode(_fileno(stream), _O_U16TEXT);
}

#else

static int consileWide(FILE *stream)
{
    return fwide(stream, 1);
    
}

#endif

void init() {
    setlocale(LC_ALL, "");
}

//!--------------------

unsigned char game[9][9] = {0};

unsigned char currentPlayer = 0;
unsigned char currentGlobal = 0;

int main() {
    init();

    consoleWide(stdout);
    wprintf(L"HELLO1 %d, %d\n", game[0][0], game[1][5]);

    scanf(" ");
    return 0;
}