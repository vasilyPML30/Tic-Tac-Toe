#include "NcursesView.h"
#include <ncurses.h>

NcursesView::NcursesView(Board &board): _board(board)
{
    _x = 0;
    _y = 0;
}

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
    char sign = 'O';
    initscr();
    raw();
    noecho();
    showBoard();
    while (curState == GAME)
    {
        mvprintw(_board.getH(), 0, "%c Move.\n", sign);
        if (!_getInput())
        {
            curState = DRAW;
            break;
        }
        _board.move(_x, _y, sign);
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
        mvprintw(_board.getH(), 0, "%c wins!\nPress any key to exit\n", (result == NOUGHTS ? 'O' : 'X'));
    getch();
}

bool NcursesView::_getInput()
{
    while (true)
    {
        move(_y, _x);
        char ch = getch();
        switch (ch)
        {
            case 65:
                if (_y > 0)
                    _y--;
                break;
            case 66:
                if (_y < _board.getH() - 1)
                    _y++;
                break;
            case 67:
                if (_x < _board.getW() - 1)
                    _x++;
                break;
            case 68:
                if (_x > 0)
                    _x--;
                break;
            case 'x':
                return false;
            case ' ':
                if (_board.canMove(_x, _y))
                    return true;
                break;
        }
    }
    return false;
}