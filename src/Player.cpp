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
                     int height, int width, int len): Player("")
{
    _creator = true;
    _bName = bName;
    _bKey = bKey;
    _curlHandler = curl_easy_init();
    curl_easy_setopt(_curlHandler, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(_curlHandler, CURLOPT_WRITEFUNCTION, getResponce);
    curl_easy_setopt(_curlHandler, CURLOPT_URL,
                     ("http://vasyoid.netau.net/xo.php?command=create&name=" + 
                     _bName + "&key=" + _bKey + "&player=" + name +
                     "&h=" + std::to_string(height) + "&w=" + std::to_string(width) +
                     "&len=" + std::to_string(len)).c_str());
    curl_easy_perform(_curlHandler);
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

void WebPlayer::waitJoin()
{
    responce = "";
    curl_easy_setopt(_curlHandler, CURLOPT_URL,
                     ("http://vasyoid.netau.net/xo.php?command=check&name=" + 
                     _bName + "&key=" + _bKey).c_str());
    while (responce == "")
    {
        sleep(2);
        curl_easy_perform(_curlHandler);
    }
    while (responce.size() && (responce.back() < 'a' || 'z' < responce.back()))
        responce.pop_back();
    _name = responce;
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
            return true;
        }
    }
}