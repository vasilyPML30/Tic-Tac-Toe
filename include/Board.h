#ifndef _BOARD_H_
#define _BOARD_H_

enum state {CROSSES, NOUGHTS, DRAW, GAME};

class Board
{
public:
    Board(int height, int width, int length);
    ~Board();
    void move(int x, int y, int sign);
    bool canMove(int x, int y) const;
    state isWin() const;
    char getCell(int x, int y) const;
    int getH() const;
    int getW() const;
    int getLen() const;
private:
    Board (const Board &b);
    Board & operator=(const Board &b);
    bool isInside(int x, int y) const;
    char **_field;
    int _height;
    int _width;
    int _lenToWin;
};


#endif