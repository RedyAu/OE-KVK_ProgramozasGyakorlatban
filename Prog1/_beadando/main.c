//! INCLUDES
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

#define XMark 0
#define OMark 1

#define BoardTemplate L"┌───┬───┬───┐\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n└───┴───┴───┘"
#define SelectedL L"╔═══╗        \n║   ║        \n║   ║        \n║   ║        \n╚═══╝        "
#define SelectedC L"    ╔═══╗    \n    ║   ║    \n    ║   ║    \n    ║   ║    \n    ╚═══╝    "
#define SelectedR L"        ╔═══╗\n        ║   ║\n        ║   ║\n        ║   ║\n        ╚═══╝"
#define AdditionalLine L"             \n"

void init() {
    setlocale(LC_ALL, "");
    consoleWide(stdout);
}

//! GLOBALS
unsigned char game[9][9] = {0}; //* Storing all marks. First dim: Global board states, Second dim: Local board states.

unsigned char aiEnabled = 0; //* 0 = 2 Player Mode; 1 = AI vs Player

unsigned char Player = 0; //* 0 = X; 1 = O
unsigned char selectedBoard = 0; //* 1-9 = Boards; 0 = User has to select board before next move.

//! PROTOTYPES
void greet();
unsigned char getMove();

void getHLine(wchar_t *);
void printGame();
void superpose(wchar_t *original, wchar_t *additional, wchar_t *result);
void extendLines(unsigned char additionalLines, wchar_t *source);

//! MAIN LOOP
int main() {
    init();

    /*

    wchar_t originalString[250];
    wcscpy(originalString, L"┌───┬───┬───┐\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n└───┴───┴───┘");
    wchar_t additionalString[250];
    wcscpy(additionalString, L"    ╔═══╗    \n    ║   ║    \n    ║   ║    \n    ║   ║    \n    ╚═══╝    ");
    wchar_t resultString[250];

    superpose(originalString, additionalString, resultString);

    wprintf(L"%s", resultString);

    return 0;

    */

    greet();

    printGame();

    while (1) {
        if (selectedBoard == 0) {
            do {
                wprintf(L"\nChoose a board with your numeric keyboard!\n");
                selectedBoard = getMove();
            } while (0);//!isValidBoard(selectedBoard));

            printGame();
        }
    }
    scanf(" ");
    return 0;
}

//! FUNCTIONS

void printGame() {
    wchar_t board[250] = {0};
    wcscpy(board, BoardTemplate);

    wchar_t selectedBoardDisplay[250] = {0};
    if (selectedBoard) {
        if ((selectedBoard == 1) || (selectedBoard == 4) || (selectedBoard == 7)) {
            wcscpy(selectedBoardDisplay, SelectedL);
            extendLines(((2 - (selectedBoard / 3)) * 4), selectedBoardDisplay);
        } else if ((selectedBoard == 2) || (selectedBoard == 5) || (selectedBoard == 8)) {
            wcscpy(selectedBoardDisplay, SelectedC);
            extendLines(((2 - (selectedBoard / 3)) * 4), selectedBoardDisplay);
        } else {
            wcscpy(selectedBoardDisplay, SelectedR);
            extendLines(((3 - (selectedBoard / 3)) * 4), selectedBoardDisplay);
        }
        superpose(board, selectedBoardDisplay, board);
    }

    wprintf(L"\n\n%s", board);

    return;
}

void extendLines(unsigned char additionalLines, wchar_t *source) {
    wchar_t result[250] = {0};

    while(additionalLines > 0) {
        wcscat(result, AdditionalLine);
        additionalLines--;
    }
    wcscat(result, source);
    wcscpy(source, result);
    return;
}

void superpose(wchar_t *original, wchar_t *additional, wchar_t *result) {
    wcscpy(result, original);
/*
    wprintf(L"\nOriginal:\n%s", original);
    wprintf(L"\nSuperposed:\n%s", additional);
*/
    int length = wcslen(additional);
    unsigned char i = 0;
    while (i < length) {
        //* Change original text to additional layer on every character additional is not a space
        *(result + i) = ((*(additional + i) == L' ') ? *(original + i) : *(additional + i));
        i++;
    }
    return;
}

unsigned char getMove() {
    wchar_t move = 0;
    do {
        wprintf(L"Type 1-9: ");
        move = _getwch();
    } while (!(move >= L'1' && move <= L'9'));
    move -= L'0';
    return (unsigned char)move;
}

void greet() {
    wprintf(L"Starting Ultimate Tic-Tac-Toe!\n");
    wprintf(L"\nWho is playing?\n\n1: Only me (AI mode)\n2: Me and my buddy (2 Player mode)");
    do {
        wprintf(L"\nType 1-2: ");
        aiEnabled = _getwch();
    } while (aiEnabled != L'1' && aiEnabled != L'2');

    //* aiEnabled now has an ASCII representation of 1 or 2 in it.
    //* Changing it to numeric values used later in the program.

    if (aiEnabled == '1') {
        aiEnabled = 1;
        wprintf(L"Selected AI mode.\n");
    } else {
        aiEnabled = 0;
        wprintf(L"Selected 2 Player mode.\n");
    }
}