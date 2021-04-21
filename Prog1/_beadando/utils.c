#include "globals.h"

unsigned char getWinningFor(unsigned char player, unsigned char board);
unsigned char winCheck(unsigned char *board, unsigned char player);
unsigned char isDraw(unsigned char *board);
unsigned char isValidBoard(unsigned char board, unsigned char userSelected);
unsigned char isValidMove(unsigned char move, unsigned char userSelected);

unsigned char getWinningFor(unsigned char player, unsigned char board)
{
    //* Loop trough every place on the board, try placing mark, see if it is a winning move.
    //* If sabotage, check winning move for other player.
    int i;

    unsigned char testBoard[9];
    for (i = 0; i < 9; i++) //! Get a separate board to test moves with
    {
        testBoard[i] = localBoards[board][i];
    }

    for (i = 0; i < 9; i++)
    {
        unsigned char backupMark = testBoard[i];
        testBoard[i] = player + 1;
        if (isValidMove(i, 0) && winCheck(testBoard, player))
        {
            return i;
        }
        testBoard[i] = backupMark;
    }

    return 9;
}

unsigned char winCheck(unsigned char *board, unsigned char player)
{
    unsigned int state = 0;
    int i;

    //wprintf(L"\n#### WINCHECK Local: %d, Player: %d", local, player);

    for (i = 0; i < 9; i++)
        state |= ((board[i] == (player + 1)) << (8 - i));

    //wprintf(L"\nAggregated board: %x", state);

    for (i = 0; i < 8; i++)
    {
        unsigned int check = state & WinMasks[i];
        check |= ~(WinMasks[i]);

        //wprintf(L"\nChecking state: %x against mask: %x, got value: %x", state, WinMasks[i], check);

        if (check == 0xFFFFFFFF)
        {
            //wprintf(L"\n--\nWon!");
            return 1;
        }
    }
    return 0;
}

unsigned char isDraw(unsigned char *board)
{
    unsigned char isDraw = 0;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (board[i])
            isDraw++;
    }
    isDraw = (isDraw == 9);

    return isDraw;
}

unsigned char isValidBoard(unsigned char selectedBoard, unsigned char userSelected)
{
    if (globalBoard[selectedBoard])
    {
        if (userSelected)
            wprintf(L"\nThis board can't be selected!");
        return 0;
    }
    else
        return 1;
}

unsigned char isValidMove(unsigned char move, unsigned char userSelected)
{
    if (localBoards[selectedBoard][move])
    {
        if (userSelected)
            wprintf(L"\nThis move is not valid!");
        return 0;
    }
    else
        return 1;
}