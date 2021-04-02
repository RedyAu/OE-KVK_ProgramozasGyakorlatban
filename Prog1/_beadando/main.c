//! INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

#define Version L"v1.0"
#define UTTTLogo L"\n█░█ █░░ ▀█▀ █ █▀▄▀█ ▄▀█ ▀█▀ █▀▀\n█▄█ █▄▄ ░█░ █ █░▀░█ █▀█ ░█░ ██▄\n\n▀█▀ █ █▀▀ ▄▄ ▀█▀ ▄▀█ █▀▀ ▄▄ ▀█▀ █▀█ █▀▀\n░█░ █ █▄▄ ░░ ░█░ █▀█ █▄▄ ░░ ░█░ █▄█ ██▄"
#define BoardTemplate L"┌───┬───┬───┐\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n├───┼───┼───┤\n│   │   │   │\n│   │   │   │\n│   │   │   │\n└───┴───┴───┘"
#define SelectedL L"╔═══╗        \n║   ║        \n║   ║        \n║   ║        \n╚═══╝        "
#define SelectedC L"    ╔═══╗    \n    ║   ║    \n    ║   ║    \n    ║   ║    \n    ╚═══╝    "
#define SelectedR L"        ╔═══╗\n        ║   ║\n        ║   ║\n        ║   ║\n        ╚═══╝"
#define AdditionalLine L"             \n"
#define XPlays L" \\ /\n  X   PLAYS\n / \\\n"
#define OPlays L"\n ┌─┐\n │ │  PLAYS\n └─┘\n"
#define XWon L"\n \\ /\n  X   WON THE GAME!\n / \\\n"
#define OWon L"\n ┌─┐\n │ │  WON THE GAME!\n └─┘"

const unsigned int WinMasks[8] = {0b100100100, 0b010010010, 0b001001001, 0b111000000, 0b000111000, 0b000000111, 0b100010001, 0b001010100};

void init() {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    consoleWide(stdout);
}

//! GLOBALS
unsigned char globalBoard[9] = {/*1,1,0,0,0,0,0,0,*/0};
unsigned char localBoards[9][9] = {{0},{0},{0/*,2,2,2,1,2,2,1,1*/},{0},{0},{0},{0},{0},{0}}; //* Storing all marks. First dim: Global board states, Second dim: Local board states.

unsigned char aiEnabled = 0; //* 0 = 2 Player Mode; 1 = AI vs Player

unsigned char player = 0; //* 0 = X; 1 = O
unsigned char selectedBoard = 9; //* 0-8 = Boards; 9 = User has to select board before next move.

//! PROTOTYPES
void greet();
unsigned char getMove();
void printGame();
void superpose(wchar_t *original, wchar_t *additional, wchar_t *result);
void extendLines(unsigned char additionalLines, wchar_t *source);
unsigned char isValidBoard(unsigned char board, unsigned char userSelected);
unsigned char isValidMove(unsigned char move, unsigned char userSelected);
unsigned char winCheck(unsigned char local);
void gameOver(unsigned char win);
unsigned char isDraw(unsigned char local);
unsigned char random();

//! MAIN LOOP
int main() {
    init();

    greet();

    while (1) {
        wprintf(L"\n\n===================================");

        unsigned char move = 0;

        if (aiEnabled && player) {
            if (selectedBoard == 9) {
                do {
                    selectedBoard = random();
                } while (!isValidBoard(selectedBoard, 0));
            }

            do {
                move = random();
            } while (!isValidMove(move, 0));

        } else {

            if (selectedBoard == 9) {
                printGame();
                do {
                    wprintf(L"\n\nChoose a board with your numeric keyboard!\n");
                    selectedBoard = getMove();
                } while (!isValidBoard(selectedBoard, 1));
            }

            printGame();

            do {
                wprintf(L"\n\nChoose a field to place a mark with your numeric keyboard!\n");
                move = getMove();
            } while (!isValidMove(move, 1));
        }
        localBoards[selectedBoard][move] = player + 1;

        if (winCheck(1)) {
            if (!aiEnabled) wprintf(L"\n\n - You won a small board! -\n");
            globalBoard[selectedBoard] = player + 1;

            if (winCheck(0)) {
                printGame();
                gameOver(1);
                return 0; // Exit the program
            } else if (isDraw(0)) {
                printGame();
                gameOver(0);
                return 0;
            }
        } else if (isDraw(1)) {
            if (isDraw(0)) {
                printGame();
                gameOver(0);
                return 0;
            }
        }

        if (aiEnabled) printGame();

        if (isValidBoard(move, 0)) selectedBoard = move;
        else selectedBoard = 9;
        
        player ^= 0x01;
    }
    scanf(" ");
    return 0;
}

//! FUNCTIONS
unsigned char random() {
    return rand() % 9;
}

unsigned char winCheck(unsigned char local) {
    unsigned int state = 0;
    int i;

    //wprintf(L"\n#### WINCHECK Local: %d, Player: %d", local, player);

    for (i = 0; i < 9; i++) state |= (((local ? localBoards[selectedBoard][i] : globalBoard[i]) == (player + 1)) << (8 - i));

    //wprintf(L"\nAggregated board: %x", state);

    for (i = 0; i < 8; i++) {
        unsigned int check = state & WinMasks[i];
        check |= ~(WinMasks[i]);

        //wprintf(L"\nChecking state: %x against mask: %x, got value: %x", state, WinMasks[i], check);

        if (check == 0xFFFFFFFF) {
            //wprintf(L"\n--\nWon!");
            return 1;
        }
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
        
            //Is the current local board won? (3 is TIE)
            if (globalBoard[boardI] != 0 && globalBoard[boardI] != 3) {
                unsigned char oWon = globalBoard[boardI] - 1;

                switch (placeI)
                {
                case 0:
                    mark = oWon ? L'┌' : L'\\';
                    break;
                case 1:
                    mark = oWon ? L'─' : L' ';
                    break;
                case 2:
                    mark = oWon ? L'┐' : L'/';
                    break;
                case 3:
                    mark = oWon ? L'│' : L' ';
                    break;
                case 4:
                    mark = oWon ? L' ' : L'X';
                    break;
                case 5:
                    mark = oWon ? L'│' : L' ';
                    break;
                case 6:
                    mark = oWon ? L'└' : L'/';
                    break;
                case 7:
                    mark = oWon ? L'─' : L' ';
                    break;
                case 8:
                    mark = oWon ? L'┘' : L'\\';
                    break;
                default:
                    break;
                }
            }
            else {
                mark = ((localBoards[boardI][placeI] == 0) ? L' ' : ((localBoards[boardI][placeI] == 1) ? L'X' : L'O'));
            }
            
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

    wprintf(L"\n\n\n%s\n%s", (player ? OPlays : XPlays), board);

    return;
}

void gameOver(unsigned char win) {
    wchar_t playerChar = (player == 1) ? L'O' : L'X';

    if (win) {
        wprintf(L"\n\n===================================\n%s\n", (player ? OWon : XWon));
    } else {
        wprintf(L"\n\n===================================\n     GAME ENDED WITH TIE :(\n");
    }
    
    wprintf(L"\nPress enter to exit.\n");
    getchar();
    return;
}

unsigned char isDraw(unsigned char local) {
    unsigned char isDraw = 0;
    int i;
    for (i = 0; i < 9; i++) {
        if (!local ? globalBoard[i] : localBoards[selectedBoard][i]) isDraw++;
    }
    isDraw = (isDraw == 9);

    //wprintf(L"\n#### isDraw: %d; global: %d", isDraw, global);
    
    if (isDraw && local) globalBoard[selectedBoard] = 3; //Set global board to occupied

    return isDraw;
}

unsigned char isValidBoard(unsigned char selectedBoard, unsigned char userSelected) {
    if (globalBoard[selectedBoard] || isDraw(1)) {
        if (userSelected) wprintf(L"\nThis board can't be selected!");
        return 0;
    } else return 1;
}

unsigned char isValidMove(unsigned char move, unsigned char userSelected) {
    if (localBoards[selectedBoard][move]) {
        if (userSelected) wprintf(L"\nThis move is not valid!");
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
    wprintf(L"\n\n%s\nBy Benedek Fodor (G2NFHW)  %s\n\n   - NEW GAME -\n\nWho is playing?\n\n1: Only me (AI mode)\n2: Me and my buddy (2 Player mode)", UTTTLogo, Version);
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