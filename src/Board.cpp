#include "Board.h"
#include <algorithm>

Board::Board(int height, int width, int length) {
    _height = height;
    _width = width;
    _lenToWin = length;
    char *field = new char[_height * _width];
    std::fill(field, field + height * width, '.');
    _field = new char *[_height];
    for (int i = 0; i < _height; i++)
        _field[i] = &field[i * _width];
}

Board::~Board() {
    delete[] _field[0];
    delete[] _field;
}

void Board::move(int x, int y, int sign) {
    _field[y][x] = sign;
}

bool Board::canMove(int x, int y) const {
    return  isInside(x, y) && _field[y][x] == '.';
}

state Board::isWin() const {
    bool draw = true;
    for (int y = 0; y < _height; y++)
        for (int x = 0; x < _width; x++) {
            char sign = _field[y][x];
            bool rightWin = true;
            bool downWin = true;
            bool diagDownWin = true;
            bool diagUpWin = true;
            if (sign == '.') {
                draw = false;
                continue;
            }
            for (int shift = 0; shift < _lenToWin; shift++) {
                if (_width <= x + shift || _field[y][x + shift] != sign)
                    rightWin = false;
                if (_height <= y + shift || _field[y + shift][x] != sign)
                    downWin = false;
                if (_width <= x + shift || _height <= y + shift ||
                    _field[y + shift][x + shift] != sign)
                    diagDownWin = false;
                if (_width <= x + shift || y - shift < 0 ||
                    _field[y - shift][x + shift] != sign)
                    diagUpWin = false;
            }
            if (rightWin || downWin || diagDownWin || diagUpWin)
                return sign == 'X' ? CROSSES : NOUGHTS;
        }
    return draw ? DRAW : GAME;
}

char Board::getCell(int x, int y) const {
    if (isInside(x, y))
        return _field[y][x];
    return '?';
}

int Board::getH() const {
    return _height;
}

int Board::getW() const {
    return _width;
}

int Board::getLen() const {
    return _lenToWin;
}

bool Board::isInside(int x, int y) const {
    return 0 <= x && x < _width && 0 <= y && y < _height;
}