#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Board.h"
#include <string>
#include <ncurses.h>
#include <curl/curl.h>

class Player
{
public:
    Player(std::string _name);
    virtual ~Player();
    virtual bool getInput(int &x, int &y, Board &board) = 0;
    virtual void oppMove(int x, int y);
    std::string getName() const;
protected:
    std::string _name;
    int _x;
    int _y;
    int _number;
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
    WebPlayer(std::string name, std::string bName, std::string bKey,
              int height, int width, int len);
    ~WebPlayer();
    bool getInput(int &x, int &y, Board &board);
    void oppMove(int x, int y);
    void waitJoin();
    static std::size_t getResponce(void *ptr, std::size_t size, std::size_t nmemb, void *stream);
private:
    bool _creator;
    std::string _bName, _bKey;
    CURL *_curlHandler;
    static std::string responce;
};

#endif