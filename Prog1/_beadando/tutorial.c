#include <wchar.h>

const wchar_t tutorial[4][780] = {
    L"\t ===============\n\t How to play 1/4\n\t ===============\n\n\tDo you know TicTacToe? It's a game where you have to have 3 Xs or Os in a row, column, or diagonally to win.\n\tThis is a regular TicTacToe game that X has won:\n\n\t┌───┐\n\t│X O│\n\t│OO │\n\t│XXX│\n\t└───┘\n\n\tSo far so good right?\n\tPress Enter to continue.",
    L"\t ===============\n\t How to play 2/4\n\t ===============\n\n\tNow let's say, we have 3x3 TicTacToe boards.\n\tThis is Ultimate TicTacToe!\n\tThe following game was won by O:\n\n\t┌───┬───┬───┐\n\t│OOX│\\ /│\\ /│\n\t│XX │ X │ X │\n\t│OOO│/ \\│/ \\│\n\t├───┼───┼───┤\n\t│┌─┐│┌─┐│┌─┐│\n\t││ │││ │││ ││\n\t│└─┘│└─┘│└─┘│\n\t╔═══╗───┼───┤\n\t║X  ║XX │┌─┐│\n\t║X  ║ X ││ ││\n\t║   ║ O │└─┘│\n\t╚═══╝───┴───┘\n\n\tAs you can see, in order to win the whole game, you have to win the little boards so that they form a row, column or a diagonal.\n\n\tIf you feel ready, press Enter to continue.",
    L"\t ===============\n\t How to play 3/4\n\t ===============\n\n\tThere is a catch, however. We have to make this exciting.\n\tYou can only place a mark in the Selected Board.\n\tIn the beginning, X can choose one, but after that the selection moves by itself (unless it would be invalid) like this:\n\n\tLet's zoom in on the current selected board: X has placed a mark in the top right just now:\n\t╔═══╗\n\t║  X║\n\t║   ║\n\t║   ║\n\t╚═══╝\n\n\tThis means that the top-right board will be selected in O's move (unless invalid, in which case he can choose):\n\t┌───┬───╔═══╗\n\t│   │   ║   ║\n\t│   │   ║   ║\n\t│   │   ║   ║\n\t├───┼───╚═══╝\n\t│  X│   │   │\n\t│   │   │   │\n\t│   │   │   │\n\t├───┼───┼───┤\n\t│   │   │   │\n\t│   │   │   │\n\t│   │   │   │\n\t└───┴───┴───┘\n\n\tPress Enter to continue. Only one page left.",
    L"\t ===============\n\t How to play 4/4\n\t ===============\n\n\tSo this is your goal:\n\tWin the small boards to win on the Big Board, but also to mind where in the small board you place your marks, as that controls where your opponent can play.\n\n\tHave fun!\n\n\tPress Enter to return to the Main Menu."
};

void showTutorial() 
{
    int i;
    for (i = 0; i < 4; i++) {
        wprintf(L"\n\n%s", tutorial[i]);
        getchar();
    }
    wprintf(L"\n------------------------------------\n\n");
    return;
}