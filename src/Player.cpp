#include "Player.h"
#include <unistd.h>
#include <cstdio>
#include <iostream>

std::string WebPlayer::responce;

Player::Player(std::string name): _name(name)
{
    _x = _y = _number = 0;
}

Player::~Player() {}
ConsolePlayer::ConsolePlayer(std::string name): Player(name) {}

WebPlayer::WebPlayer(std::string name, std::string bName, std::string bKey,
                     int &height, int &width, int &len, bool creator): Player("")
{
    _creator = creator;
    _bName = bName;
    _bKey = bKey;
    _curlHandler = curl_easy_init();
    curl_easy_setopt(_curlHandler, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(_curlHandler, CURLOPT_WRITEFUNCTION, getResponce);
    if (_creator)
    {
        curl_easy_setopt(_curlHandler, CURLOPT_URL,
                         ("http://vasyoid.netau.net/xo.php?command=create&name=" + 
                         _bName + "&key=" + _bKey + "&player=" + name +
                         "&h=" + std::to_string(height) + "&w=" + std::to_string(width) +
                         "&len=" + std::to_string(len)).c_str());
        curl_easy_perform(_curlHandler);
    }
    else
    {
        char otherName[11];
        curl_easy_setopt(_curlHandler, CURLOPT_URL,
                         ("http://vasyoid.netau.net/xo.php?command=join&name=" + 
                         _bName + "&key=" + _bKey + "&player=" + name).c_str());
        curl_easy_perform(_curlHandler);
        if (sscanf(responce.c_str(), "%s %i %i %i", otherName, &height, &width, &len) < 4)
            height = width = len = -1;
        else
            _name = otherName;
    }
}

std::size_t WebPlayer::getResponce(void *ptr, std::size_t size,
                                          std::size_t nmemb, void *stream)
{
    (void)size;
    (void)nmemb;
    (void)stream;
    responce = std::string((char *)ptr);
    return 0;
}

WebPlayer::~WebPlayer()
{
    if (_creator)
    {
        curl_easy_setopt(_curlHandler, CURLOPT_URL,
                         ("http://vasyoid.netau.net/xo.php?command=drop&name=" + 
                         _bName + "&key=" + _bKey).c_str());
        curl_easy_perform(_curlHandler);
    }
    curl_easy_cleanup(_curlHandler);
}

bool WebPlayer::waitJoin()
{
    int ch;
    char otherName[11];
    initscr();
    raw();
    noecho();
    nodelay(stdscr, TRUE);
    mvprintw(0, 0, "Waiting for opponent...");
    refresh();
    responce = "";
    curl_easy_setopt(_curlHandler, CURLOPT_URL,
                     ("http://vasyoid.netau.net/xo.php?command=check&name=" + 
                     _bName + "&key=" + _bKey).c_str());
    while (responce == "")
    {
        ch = getch();
        if (ch == 'x')
        {
           move(0, 0);
           nodelay(stdscr, FALSE);
           endwin();
           return false;
        }
        curl_easy_perform(_curlHandler);
    }
    sscanf(responce.c_str(), "%s", otherName);
    _name = otherName;
    move(0, 0);
    nodelay(stdscr, FALSE);
    endwin();
    return true;
}

void Player::oppMove(int x, int y)
{
    _number++;
    _x = x;
    _y = y;
}

void WebPlayer::oppMove(int x, int y)
{
    _number++;
    _x = x;
    _y = y;
    curl_easy_setopt(_curlHandler, CURLOPT_URL,
                         ("http://vasyoid.netau.net/xo.php?command=insert&name=" + 
                         _bName + "&key=" + _bKey + "&number=" +
                         std::to_string(_number) + "&x=" + std::to_string(_x) +
                         "&y=" + std::to_string(_y)).c_str());
    curl_easy_perform(_curlHandler);
}

std::string Player::getName() const
{
    return _name;
}

bool ConsolePlayer::getInput(int &x, int &y, Board &board)
{
    _number++;
    move(_y, _x);
    refresh();
    while (true)
    {
        move(_y, _x);
        int ch = getch();
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
    int n, ch;
    nodelay(stdscr, TRUE);
    move(_y, _x);
    refresh();
    _number++;
    curl_easy_setopt(_curlHandler, CURLOPT_URL,
                   ("http://vasyoid.netau.net/xo.php?command=get&name=" + 
                     _bName + "&key=" + _bKey + "&number=" + std::to_string(_number)).c_str());
    (void)board;
    while (true)
    {
        ch = getch();
        if (ch == 'x')
        {
            nodelay(stdscr, FALSE);
            return false;
        }
        curl_easy_perform(_curlHandler);
        sscanf(responce.c_str(), "%i %i %i", &n, &_x, &_y);
        if (n == _number)
        {
            move(_y, _x);
            x = _x;
            y = _y;
            nodelay(stdscr, FALSE);
            return (_x >= 0);
        }
    }
}