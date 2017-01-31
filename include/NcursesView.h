#ifndef _NCURSES_VIEW_H_
#define _NCURSES_VIEW_H_

#include "Board.h"

class NcursesView
{
public:
    NcursesView(Board &board);
    void showBoard() const;
    void doGameCycle();
private:
    bool _getInput();
    void _showResult(state result) const;
    Board &_board;
    int _x;
    int _y;
};

#endif