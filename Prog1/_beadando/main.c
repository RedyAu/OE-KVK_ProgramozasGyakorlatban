#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

//!Set up wide character support on Windows
#include <wchar.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>

static int set_wide_stream(FILE *stream)
{
    return _setmode(_fileno(stream), _O_U16TEXT);
}

#else

static int set_wide_stream(FILE *stream)
{
    return fwide(stream, 1);
}

#endif

void init() {
    setlocale(LC_ALL, "");
    set_wide_stream(stdout);
}

//!--------------------

unsigned char game[9][9] = {0};

int main() {
    init();
    printf("%d, %d", game[0][0], game[1], [5]);
    return 0;
}

void setBig(char type) {

}
