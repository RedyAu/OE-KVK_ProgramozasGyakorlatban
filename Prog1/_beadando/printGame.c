#include <wchar.h>
#include "printGame.h"
#include "globals.h"

void superpose(wchar_t *original, wchar_t *additional, wchar_t *result);
void extendLines(unsigned char additionalLines, wchar_t *source);

void printGame()
{
    wchar_t board[250] = {0};
    wcscpy(board, BoardTemplate);

    wchar_t localBoardsRenderContent[9][9] = {0};

    unsigned char boardI = 0;
    unsigned char placeI = 0;

    while (boardI < 9)
    {
        placeI = 0;
        while (placeI < 9)
        {
            wchar_t mark = 0;

            //? Is the current local board won? (3 is TIE)
            if (globalBoard[boardI] != 0 && globalBoard[boardI] != 3)
            {
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
            else
            {
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

        for (y = 0; y < 9; y++)
        {
            if (!(y % 3))
                wcscat(localBoardsRendered, L"             \n");

            for (x = 0; x < 9; x++)
            {
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
    if (selectedBoard != 9)
    {
        switch (selectedBoard % 3)
        {
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

void extendLines(unsigned char additionalLines, wchar_t *source)
{
    wchar_t result[250] = {0};

    while (additionalLines > 0)
    {
        wcscat(result, AdditionalLine);
        additionalLines--;
    }
    wcscat(result, source);
    wcscpy(source, result);
    return;
}

void superpose(wchar_t *original, wchar_t *additional, wchar_t *result)
{
    wcscpy(result, original);
    /*
    wprintf(L"\nOriginal:\n%s", original);
    wprintf(L"\nSuperposed:\n%s", additional);
*/
    int length = wcslen(additional);
    unsigned char i = 0;
    while (i < length)
    {
        //* Change original text to additional layer on every character additional is not a space
        *(result + i) = ((*(additional + i) == L' ') ? *(original + i) : *(additional + i));
        i++;
    }
    return;
}