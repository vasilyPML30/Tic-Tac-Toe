#include "Player.h"

Player::Player(std::string name): _name(name)
{
    _x = _y = 0;
}

ConsolePlayer::ConsolePlayer(std::string name): Player(name) {}
WebPlayer::WebPlayer(std::string name): Player(name) {}

std::string Player::getName() const
{
    return _name;
}

bool ConsolePlayer::getInput(int &x, int &y, Board &board)
{
    _x = x;
    _y = y;
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
                if (_y < board.getH() - 1)
                    _y++;
                break;
            case 67:
                if (_x < board.getW() - 1)
                    _x++;
                break;
            case 68:
                if (_x > 0)
                    _x--;
                break;
            case 'x':
                x = y = -1;
                return false;
            case ' ':
                if (board.canMove(_x, _y))
                {
                    x = _x;
                    y = _y;
                    return true;
                }
                break;
        }
    }
    x = y = -1;
    return false;
}

bool WebPlayer::getInput(int &x, int &y, Board &board)
{
    x = y = -1;
    board.getH();
    return false;
}