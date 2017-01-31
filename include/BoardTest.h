#ifndef _BOARD_TEST_H_
#define _BOARD_TEST_H_

#include "Test.h"
#include "Board.h"

class BoardTest: public Test
{
public:
    void testMove() const;
    void testCanMove() const;
    void testIsWin() const;
    void testGetCell() const;
    void runAllTests() const;
private:
    void refreshBoard(Board &m) const;
    void fillLine(Board &m, int x, int y, int dx, int dy, char sign) const;
};

#endif