#include "Board.h"
#include "BoardView.h"
#include "NcursesView.h"
#include <cstring>

int main(int argc, char **argv)
{
    Board board(20, 120, 5);
    bool silent = argc > 1 && !strcmp(argv[1], "silent");
    TextView textView(board, silent);
    NcursesView ncursesView(board);
    if (argc > 1 && !strcmp(argv[1], "curses"))
        ncursesView.doGameCycle();
    else
        textView.doGameCycle();
    return 0;
}