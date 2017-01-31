#ifndef _BOARD_VIEW_H_
#define _BOARD_VIEW_H_

#include "Board.h"

class TextView
{
public:
    TextView(Board &board, bool silent);
    void showBoard() const;
    void doGameCycle();
private:
    void _readInput(int &x, int &y, char sign) const;
    void _showResult(state result) const;
    bool _silent;
    Board &_board;
};

#endif