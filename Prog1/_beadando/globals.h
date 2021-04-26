#ifndef GlobalsH
#define GlobalsH

//! Globals

unsigned char globalBoard[9] = {0};
unsigned char localBoards[9][9] = {0}; //* Storing all marks. First dim: Global board states, Second dim: Local board states.

unsigned char aiEnabled = 0; //* 0 = 2 Player Mode; 1 = AI vs Player

unsigned char player = 0;        //* 0 = X; 1 = O
unsigned char selectedBoard = 9; //* 0-8 = Boards; 9 = User has to select board before next move.

//! Consts

#define Version L"v2.0"
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

#endif