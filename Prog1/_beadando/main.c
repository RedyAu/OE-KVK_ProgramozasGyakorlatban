//! INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>

#include "globals.h"
#include "utils.c"
#include "printGame.h"

//! PROTOTYPES
void init();
void greet();
unsigned char getMove();
void saveGame(unsigned char win);

void gameOver(unsigned char win);

//! MAIN LOOP
int main()
{
    init();

    greet();

    while (1)
    {
        wprintf(L"\n\n===================================");

        unsigned char move = 0;

        if (aiEnabled && player)
        {
            if (selectedBoard == 9)
            { //! If no local board is selected, select one at random.
                do
                    selectedBoard = rand() % 9;
                while (!isValidBoard(selectedBoard, 0));
            }

            if ((move = getWinningFor(1, selectedBoard)) != 9)
                ; //! Got a winning move for the AI!
            else if ((move = getWinningFor(0, selectedBoard)) != 9)
                ; //! Got a winning move for the other player to sabotage :evil:
            else
                do
                    move = rand() % 9;
                while (!isValidMove(move, 0)); //! No good moves :( Just choose a random valid field.

            //* No need to write move here, that happens later in the code.
        }
        else
        {
            //! Get move from user

            if (selectedBoard == 9)
            {
                printGame(NULL);
                do
                {
                    wprintf(L"\n\nChoose a board with your numeric keyboard!\n");
                    selectedBoard = getMove();
                } while (!isValidBoard(selectedBoard, 1));
            }

            printGame(NULL);

            do
            {
                wprintf(L"\n\nChoose a field to place a mark with your numeric keyboard!\n");
                move = getMove();
            } while (!isValidMove(move, 1));
        }
        //! Save move
        localBoards[selectedBoard][move] = player + 1;

        //* #######################################

        if (winCheck(localBoards[selectedBoard], player)) //! Check win on the current local board
        {
            if (!aiEnabled)
                wprintf(L"\n\n - You won a small board! -\n"); //! Announce win if a user won
            globalBoard[selectedBoard] = player + 1;           //! Save won board in global board

            if (winCheck(globalBoard, player)) //! Check win on global board
            {
                printGame(NULL);
                gameOver(1); //! Announce WIN, GAME OVER!
                return 0;
            }
            else if (isDraw(globalBoard)) //! If there is no winner, check for global draw
            {
                printGame(NULL);
                gameOver(0); //! Announce TIE, GAME OVER!
                return 0;
            }
        }
        else if (isDraw(localBoards[selectedBoard])) //! Check for local draw
        {
            //* If current board is not won and is tie, set global mark to tie
            if (!globalBoard[selectedBoard])
                globalBoard[selectedBoard] = 3;

            if (isDraw(globalBoard)) //! Check for global tie
            {
                printGame(NULL);
                gameOver(0); //! Announce TIE, GAME OVER!
                return 0;
            }
        }

        if (aiEnabled)
            printGame(NULL);

        if (isValidBoard(move, 0))
            selectedBoard = move;
        else
            selectedBoard = 9;

        player ^= 1;
    }
    return 0;
}

//! FUNCTIONS

void init()
{
    srand(time(NULL));
    setlocale(LC_ALL, "UTF-8");
    _setmode(_fileno(stdout), _O_U16TEXT);
}

void gameOver(unsigned char win)
{
    wchar_t playerChar = (player == 1) ? L'O' : L'X';

    if (win)
    {
        wprintf(L"\n\n===================================\n%s\n", (player ? OWon : XWon));
    }
    else
    {
        wprintf(L"\n\n===================================\n     GAME ENDED WITH TIE :(\n");
    }
    
    wprintf(L"\nWould you like to save the final board to a file?\n0: Exit\n1: Save board, then exit");

    wchar_t pressed = 0;
    do
    {
        wprintf(L"\nType 0-1: ");
        pressed = _getwche();
    } while (!(pressed == L'0' || pressed == L'1'));
    
    if (pressed == L'1') {
        saveGame(win);
        wprintf(L"\n\nPress any key to exit.");
        _getwch();
    }

    return;
}

void saveGame(unsigned char win) {
    wprintf(L"\nSaving...");
    wchar_t board[250] = {0};
    printGame(board); //* Get rendered board to print to file

    FILE *fp;
    fp = fopen("game.txt", "w");
    _setmode(_fileno(fp), _O_U16TEXT);

    if (fp == NULL) {
        wprintf(L"\nCouldn't save file!");
        return;
    }
    
    fwprintf(fp, L"\n%s\n\n%s", board, (win ? (player ? OWon : XWon) : L"Game ended with tie :("));
    fflush(fp);
    fclose(fp);
}

unsigned char getMove()
{
    wchar_t move = 0;
    do
    {
        wprintf(L"Type 1-9: ");
        move = _getwche();
    } while (!(move >= L'1' && move <= L'9'));
    move -= (L'0' + 1);
    if (move > 5)
        move -= 6;
    else if (move < 3)
        move += 6;

    return ((unsigned char)move);
}

#include "tutorial.c"

void greet()
{
    wprintf(L"\n\n%s\nBy Benedek Fodor (G2NFHW)  %s\n", UTTTLogo, Version);
    while (1)
    {
        wprintf(L"\n   - NEW GAME -\n\nWho is playing?\n\n0: How to play?\n\n1: Only me (AI mode)\n2: Me and my buddy (2 Player mode)");
        do
        {
            wprintf(L"\nType 0-2: ");
            aiEnabled = _getwch();
        } while (aiEnabled < '0' || aiEnabled > '2');

        //* aiEnabled now has an ASCII representation of 1 or 2 in it.
        //* Changing it to numeric values used later in the program.

        if (aiEnabled == '0') {
            showTutorial();
        } else if (aiEnabled == '1') {
            aiEnabled = 1;
            wprintf(L"Selected AI mode.\n\nYou are X, AI is O.\n");
            break;
        } else {
            aiEnabled = 0;
            wprintf(L"Selected 2 Player mode.\n");
            break;
        }
    }
}