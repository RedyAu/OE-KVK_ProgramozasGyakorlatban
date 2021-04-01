//! INCLUDES
#include <stdlib.h>
#include <stdio.h>

//!Set up wide character support on Windows
#include <wchar.h>
#include <locale.h>

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

#define BoardTemplate L"┌───┬───┬───┐\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n└───┴───┴───┘"
#define SelectedL L"╔═══╗        \n║   ║        \n║   ║        \n║   ║        \n╚═══╝        "
#define SelectedC L"    ╔═══╗    \n    ║   ║    \n    ║   ║    \n    ║   ║    \n    ╚═══╝    "
#define SelectedR L"        ╔═══╗\n        ║   ║\n        ║   ║\n        ║   ║\n        ╚═══╝"
#define AdditionalLine L"             \n"

const unsigned int WinMasks[8] = {0b100100100, 0b010010010, 0b001001001, 0b111000000, 0b000111000, 0b000000111, 0b100010001, 0b001010100};

void init() {
    setlocale(LC_ALL, "");
    consoleWide(stdout);
}

//! GLOBALS
unsigned char globalBoard[9] = {0};
unsigned char localBoards[9][9] = {0};//{{1,1,2,0,1,2,2,1,0},{0},{0},{0},{0},{0},{0},{0},{0}}; //* Storing all marks. First dim: Global board states, Second dim: Local board states.

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
unsigned char winCheck(unsigned char local);
void win();

//! MAIN LOOP
int main() {
    init();
    greet();

    printGame();

    while (1) {
        wprintf(L"\n\n=============\n\n");
        if (player) wprintf(L"\nO plays next!\n");
        else wprintf(L"\nX plays next!\n");

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

        if (winCheck(1)) {
            wprintf("\nYou won the local board!\n");
            globalBoard[selectedBoard] = player + 1;
            if (winCheck(0)) {
                printGame();
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
unsigned char winCheck(unsigned char local) {
    unsigned int state = 0;
    int i;

    for (i = 0; i < 9; i++) state |= (((local ? localBoards[selectedBoard][i] : globalBoard[i]) == (player + 1))<<i);

    for (i = 0; i < 9; i++) {
        unsigned int check = 0;
        check = state ^ WinMasks[i];

        if (!check) return 1;
    }
    return 0;
}

void printGame() {
    wchar_t board[250] = {0};
    wcscpy(board, BoardTemplate);

    wchar_t localBoardsRenderContent[9][9] = {0};
    
    unsigned char boardI = 0;
    unsigned char placeI = 0;

    while (boardI < 9) {
        placeI = 0;
        while (placeI < 9) {
            wchar_t mark = 0;
            mark = ((localBoards[boardI][placeI] == 0) ? L' ' : ((localBoards[boardI][placeI] == 1) ? L'X' : L'O'));
            
            unsigned char renderX = ((boardI % 3) * 3) + (placeI % 3);
            unsigned char renderY = ((boardI / 3) * 3) + (placeI / 3);

            localBoardsRenderContent[renderX][renderY] = mark;
            placeI++;
        }
        boardI++;
    }
    wchar_t localBoardsRendered[250] = {0};
    {
        unsigned char x = 0;
        unsigned char y = 0;

        for (y = 0; y < 9; y++) {
            if (!(y % 3))
                wcscat(localBoardsRendered, L"             \n");
                
            for (x = 0; x < 9; x++) {
                if (!(x % 3))
                    wcscat(localBoardsRendered, L" ");

                wchar_t stringToCopy[2] = {0};
                stringToCopy[0] = localBoardsRenderContent[x][y];
                wcscat(localBoardsRendered, stringToCopy);
            }
            wcscat(localBoardsRendered, L" \n");
        }
    }
    superpose(board, localBoardsRendered, board);

    wchar_t selectedBoardDisplay[250] = {0};
    if (selectedBoard != 9) {
        switch (selectedBoard % 3) {
            case 0:
                wcscpy(selectedBoardDisplay, SelectedL);
                extendLines((((selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
            case 1:
                wcscpy(selectedBoardDisplay, SelectedC);
                extendLines((((selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
            case 2:
                wcscpy(selectedBoardDisplay, SelectedR);
                extendLines((((selectedBoard) / 3) * 4), selectedBoardDisplay);
                break;
        }
        superpose(board, selectedBoardDisplay, board);
    }


    wprintf(L"\n%s", board);

    return;
}

void win() {
    wchar_t playerChar = (player == 1) ? L'O' : L'X';

    wprintf(L"\n\n===================================\n        %c WON THE GAME!\n\nPress any key to exit.\n", playerChar);
    getchar();
    return;
}

unsigned char isValidBoard(unsigned char board, unsigned char userSelected) {
    //TODO handle draws
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
        move = _getwche();
    } while (!(move >= L'1' && move <= L'9'));
    move -= (L'0' + 1);
    if (move > 5) move -= 6;
    else if (move < 3) move += 6;
    
    return ((unsigned char)move);
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