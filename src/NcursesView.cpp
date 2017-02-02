#include "NcursesView.h"
#include <ncurses.h>
#include <unistd.h>

NcursesView::NcursesView(Board &board, Player &p1, Player &p2):
                        _board(board), _player1(p1), _player2(p2) {}

void NcursesView::showBoard() const
{
    for (int y = 0; y < _board.getH(); y++)
    {
        for (int x = 0; x < _board.getW(); x++)
            printw("%c", _board.getCell(x, y));
        printw("\n");
    }
}

void NcursesView::doGameCycle()
{
    state curState = GAME;
    char sign = 'X';
    int x = 0, y = 0;
    initscr();
    raw();
    noecho();
    showBoard();
    while (curState == GAME)
    {
        Player &player = (sign == 'X' ? _player1 : _player2);
        mvprintw(_board.getH(), 0, "%s Move (%c).\n", player.getName().c_str(), sign);
        if (!player.getInput(x, y, _board))
        {
            curState = DRAW;
            break;
        }
        _board.move(x, y, sign);
        (sign == 'X' ? _player2 : _player1).oppMove(x, y);
        addch(sign);
        sign = (sign == 'O' ? 'X' : 'O');
        curState = _board.isWin();
    }
    _showResult(curState);
    endwin();
}

void NcursesView::_showResult(state result) const
{
    if (result == DRAW)
        mvprintw(_board.getH(), 0, "Draw.\nPress any key to exit\n");
    else
        mvprintw(_board.getH(), 0, "%s wins!\nPress any key to exit\n",
                                   (result == CROSSES ? _player1 : _player2).getName().c_str());
    getch();
}