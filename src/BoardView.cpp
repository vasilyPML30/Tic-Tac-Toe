#include "BoardView.h"
#include <cstdio>

TextView::TextView(Board &board, bool silent): _board(board)
{
    _silent = silent;
}

void TextView::showBoard() const
{
    printf("\n");
    for (int y = 0; y < _board.getH(); y++)
    {
        for (int x = 0; x < _board.getW(); x++)
            printf("%c", _board.getCell(x, y));
        printf("\n");
    }
}

void TextView::doGameCycle()
{
    state curState = GAME;
    char sign = 'O';
    while (curState == GAME)
    {
        int x, y;
        if (!_silent)
            showBoard();
        _readInput(x, y, sign);
        if (x == -1 && y == -1)
        {
            curState = DRAW;
            break;
        }
        _board.move(x, y, sign);
        sign = (sign == 'O' ? 'X' : 'O');
        curState = _board.isWin();
    }
    showBoard();
    _showResult(curState);
}

void TextView::_showResult(state result) const
{
    if (result == DRAW)
        printf("Draw.\n");
    else
        printf("%c wins!\n", (result == NOUGHTS ? 'O' : 'X'));
}

void TextView::_readInput(int &x, int &y, char sign) const
{
    while (true)
    {
        printf("%c move: ", sign);
        int read = scanf("%i %i", &y, &x);
        if (read == 2 && (_board.canMove(x, y) || (x == -1 && y == -1)))
            break;
        char errBuff[100];
        fgets(errBuff, 100, stdin);
        printf("Bad move!\n");
    }
}