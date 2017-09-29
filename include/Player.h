#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Board.h"
#include <string>
#include <curl/curl.h>

#define UP_KEY KEY_UP
#define DOWN_KEY KEY_DOWN
#define LEFT_KEY KEY_LEFT
#define RIGHT_KEY KEY_RIGHT
#define EXIT_KEY 'x'
#define SPACE_KEY 32

#ifdef _WIN32
  #include <curses.h>
  #define ENTER_KEY 13
  #define BACKSPACE_KEY 8
#else
  #include <ncurses.h>
  #define ENTER_KEY '\n'
  #define BACKSPACE_KEY 127
#endif

class Player {
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

class ConsolePlayer : public Player {
public:
    ConsolePlayer(std::string name);
    bool getInput(int &x, int &y, Board &board);
};

class WebPlayer : public Player {
public:
    WebPlayer(std::string name, std::string bName, std::string bKey,
              int &height, int &width, int &len, bool creator);
    WebPlayer(std::string name, std::string bName, std::string bKey);
    ~WebPlayer();
    bool getInput(int &x, int &y, Board &board);
    void oppMove(int x, int y);
    bool waitJoin();
    static std::size_t getResponce(void *ptr, std::size_t size, std::size_t nmemb, void *stream);
private:
    bool _creator;
    std::string _bName, _bKey;
    CURL *_curlHandler;
    static std::string responce;
};

#endif