#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Board.h"
#include <string>
#include <ncurses.h>

class Player
{
public:
    Player(std::string _name);
    virtual bool getInput(int &x, int &y, Board &board) = 0;
    std::string getName() const;
protected:
    std::string _name;
    int _x;
    int _y;
};

class ConsolePlayer : public Player
{
public:
    ConsolePlayer(std::string name);
    bool getInput(int &x, int &y, Board &board);
};

class WebPlayer : public Player
{
public:
    WebPlayer(std::string name);
    bool getInput(int &x, int &y, Board &board);
};

#endif