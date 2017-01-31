#include "Board.h"
#include "BoardView.h"
#include "NcursesView.h"
#include "Player.h"
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    ConsolePlayer Vasya("Vasya"), Petya("Petya");
    Board board(20, 20, 5);
    bool silent = argc > 1 && !strcmp(argv[1], "silent");
    TextView textView(board, silent);
    NcursesView ncursesView(board, Vasya, Petya);
    if (argc > 1 && !strcmp(argv[1], "curses"))
        ncursesView.doGameCycle();
    else
        textView.doGameCycle();
    return 0;
}