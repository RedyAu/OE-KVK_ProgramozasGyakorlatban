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
unsigned char globalBoard[9] = {0};
unsigned char localBoards[9][9] = {0}; //* Storing all marks. First dim: Global board states, Second dim: Local board states.

unsigned char aiEnabled = 0; //* 0 = 2 Player Mode; 1 = AI vs Player

unsigned char player = 0; //* 0 = X; 1 = O
unsigned char selectedBoard = 9; //* 0-8 = Boards; 9 = User has to select board before next move.

//! PROTOTYPES
void greet();
unsigned char getMove();

void getHLine(wchar_t *);
void printGame();
void superpose(wchar_t *original, wchar_t *additional, wchar_t *result);
void extendLines(unsigned char additionalLines, wchar_t *source);
unsigned char isValidBoard(unsigned char board, unsigned char userSelected);
unsigned char isValidMove(unsigned char move);
unsigned char isLocalWin();
unsigned char isGlobalWin();
void win();

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
        if (player) wprintf(L"\n\nO plays next!\n");
        else wprintf(L"\n\nX plays next!\n");

        unsigned char move = 0;

        if (selectedBoard == 9) {
            do {
                wprintf(L"\nChoose a board with your numeric keyboard!\n");
                selectedBoard = getMove();
            } while (!isValidBoard(selectedBoard, 1));
        }

        printGame();

        do {
            wprintf(L"\n\nChoose a field to place a mark with your numeric keyboard!\n");
            move = getMove();
        } while (!isValidMove(move));
        localBoards[selectedBoard][move] = player + 1;

        if (isLocalWin()) {
            //TODO Handle draws!
            globalBoard[selectedBoard] = player + 1;
            if (isGlobalWin()) {
                win();
                return 0; // Exit the program
            }
        }

        if (isValidBoard(move, 0)) selectedBoard = move;
        else selectedBoard = 9;
        
        player ^= 0x01;
    }
    scanf(" ");
    return 0;
}

//! FUNCTIONS
void printGame() {
    wchar_t board[250] = {0};
    wcscpy(board, BoardTemplate);

    wprintf(L"A");

    wchar_t selectedBoardDisplay[250] = {0};

    wprintf(L"B");

    if (selectedBoard != 9) {
        switch (selectedBoard % 3) {
            case 0:
                wcscpy(selectedBoardDisplay, SelectedL);
                extendLines((((8 - selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
            case 1:
                wcscpy(selectedBoardDisplay, SelectedC);
                extendLines((((8 - selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
            case 2:
                wcscpy(selectedBoardDisplay, SelectedR);
                extendLines((((8 - selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
        }
        superpose(board, selectedBoardDisplay, board);
    }

    wprintf(L"C");

    wchar_t localBoardsRenderContent[9][9] = {0};

    wprintf(L"D");
    
    unsigned char boardI = 0;
    unsigned char placeI = 0;

    while (boardI < 9) {
        wprintf(L"E1");
        while (placeI < 9) {
            wprintf(L"E2");
            wchar_t mark = 0;
            mark = ((localBoards[boardI][placeI] == 0) ? L' ' : ((localBoards[boardI][placeI] == 1) ? L'X' : L'O'));
            
            unsigned char renderX = ((boardI % 3) * 3) + (placeI % 3);
            unsigned char renderY = ((boardI / 3) * 3) + (placeI / 3);

            localBoardsRenderContent[renderX][renderY] = mark;
            placeI++;
        }
        boardI++;
    }
    
    //{//!Debug print
    wprintf(L"\n\nDEBUG PRINT\n");
    unsigned char x = 0;
    unsigned char y = 0;
    while (y < 9) {
        while (x < 9) {
            wprintf(L"%c.", localBoardsRenderContent[x][y]);
            x++;
        }
        wprintf(L"\n");
        y++;
    }
    //}

    /*
    wchar_t localBoardsRendered[250] = {0};
    {
        unsigned char x = 0;
        unsigned char y = 0;

        while (y < 9) {
            while (x < 9) {
                if (!(x % 3))
                    wcscat(localBoardsRendered, L" ");

                wchar_t mark = localBoardsRenderContent[x][y];
                wcscat(localBoardsRendered, &mark);
            }
            wcscat(localBoardsRendered, L"\n");

            if (!(y % 3))
                wcscat(localBoardsRendered, L"            \n");
        }
    }*/
    //superpose(board, localBoardsRendered, board);

    wprintf(L"\nBoard:\n%s", board);

    return;
}

void win() {
    wchar_t playerChar = (player == 1) ? L'O' : L'X';

    wprintf(L"\n\n===================================\n        %c WON THE GAME!\n\nPress any key to exit.\n", playerChar);
    getchar();
    return;
}

unsigned char isLocalWin() {
    return 0;
}

unsigned char isGlobalWin() {
    return 0;
}

unsigned char isValidBoard(unsigned char board, unsigned char userSelected) {
    if (globalBoard[board]) {
        if (userSelected) wprintf(L"\nThis board can't be selected!");
        return 0;
    } else return 1;
}

unsigned char isValidMove(unsigned char move) {
    if (localBoards[selectedBoard][move]) {
        wprintf(L"\nThis move is not valid!");
        return 0;
    } else return 1;
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
    return ((unsigned char)move - 1);
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
        wprintf(L"Selected AI mode.\nYou are X, AI is O.\n");
    } else {
        aiEnabled = 0;
        wprintf(L"Selected 2 Player mode.\n");
    }
}