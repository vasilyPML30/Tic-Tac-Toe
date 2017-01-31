#ifndef _NCURSES_VIEW_H_
#define _NCURSES_VIEW_H_

#include "Board.h"
#include "Player.h"
#include <string>

class NcursesView
{
public:
    NcursesView(Board &board, Player &p1, Player &p2);
    void showBoard() const;
    void doGameCycle();
private:
    void _showResult(state result) const;
    Board &_board;
    Player &_player1;
    Player &_player2;
};

#endif