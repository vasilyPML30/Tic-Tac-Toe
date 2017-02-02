#include "Board.h"
#include "BoardView.h"
#include "NcursesView.h"
#include "Player.h"
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

const int version = 1;

static int chooseMode()
{
    mvprintw(0, 0, "Welcome to tic-tac-toe! (ver %i)", version);
    mvprintw(1, 0, "Choose game mode:", version);
    mvprintw(3, 0, "Offline game");
    mvprintw(4, 0, "Create game");
    mvprintw(5, 0, "Join game");
    int x = 0, y = 3;
    while (true)
    {
        move(y, x);
        char ch = getch();
        switch (ch)
        {
            case 65:
                if (y > 3)
                    y--;
                break;
            case 66:
                if (y < 5)
                    y++;
                break;
            case ' ':
            case '\n':
                clear();
                return y - 3;
        }
    }
}

void offline(int &h, int &w, int &len, std::string &name1, std::string &name2)
{
    std::string data[6] = {"10", "10", "5", "alice", "bob"};
    int maxLen[] = {2, 2, 1, 10, 10};
    mvprintw(0, 0, "Board height:");
    mvprintw(1, 0, "Board width:");
    mvprintw(2, 0, "Number to win:");
    mvprintw(3, 0, "First player:");
    mvprintw(4, 0, "Second player:");
    mvprintw(5, 0, "Start!");
    for (int i = 0; i < 5; i++)
        mvprintw(i, 15, "%s", data[i].c_str());
    int x = 17, y = 0;
    while (true)
    {
        move(y, x);
        char ch = getch();
        if (ch == 65 && y > 0)
        {
            y--;
            x = 15 + data[y].length();
        }
        else if (ch == 66 && y < 5)
        {
            y++;
            x = 15 + data[y].length();
        }
        else if (ch == '\n' && y == 5)
        {
            clear();
            sscanf(data[0].c_str(), "%i", &h);
            sscanf(data[1].c_str(), "%i", &w);
            sscanf(data[2].c_str(), "%i", &len);
            name1 = data[3];
            name2 = data[4];
            return;
        }
        else if ('a' <= ch && ch <= 'z' && 3 <= y && y <= 4
                && (int)data[y].length() < maxLen[y])
        {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        }
        else if ('0' <= ch && ch <= '9' && y <= 2
                 && (int)data[y].length() < maxLen[y]
                 && (data[y].length() || ch != '0'))
        {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        }
        else if (ch == 127 && data[y].length())
        {
            data[y].pop_back();
            mvprintw(y, --x, " ");
            refresh();
        }
    }   
}

void create(int &h, int &w, int &len, std::string &name, std::string &bName, std::string &bKey)
{
    std::string data[7] = {"10", "10", "5", "alice", "stdboard", "123asd"};
    int maxLen[] = {2, 2, 1, 10, 10, 10};
    mvprintw(0, 0, "Board height:");
    mvprintw(1, 0, "Board width:");
    mvprintw(2, 0, "Number to win:");
    mvprintw(3, 0, "Your name:");
    mvprintw(4, 0, "Board name:");
    mvprintw(5, 0, "Board key:");
    mvprintw(6, 0, "Start!");
    for (int i = 0; i < 6; i++)
        mvprintw(i, 15, "%s", data[i].c_str());
    int x = 15, y = 0;
    while (true)
    {
        move(y, x);
        char ch = getch();
        if (ch == 65 && y > 0)
        {
            y--;
            x = 15 + data[y].length();
        }
        else if (ch == 66 && y < 6)
        {
            y++;
            x = 15 + data[y].length();
        }
        else if (ch == '\n' && y == 6)
        {
            clear();
            sscanf(data[0].c_str(), "%i", &h);
            sscanf(data[1].c_str(), "%i", &w);
            sscanf(data[2].c_str(), "%i", &len);
            name = data[3];
            bName = data[4];
            bKey = data[5];
            return;
        }
        else if ('a' <= ch && ch <= 'z' && 3 <= y
                && (int)data[y].length() < maxLen[y])
        {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        }
        else if ('0' <= ch && ch <= '9' && (y <= 2 || y == 5)
                 && (int)data[y].length() < maxLen[y]
                 && (data[y].length() || ch != '0'))
        {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        }
        else if (ch == 127 && data[y].length())
        {
            data[y].pop_back();
            mvprintw(y, --x, " ");
            refresh();
        }
    }   
}

int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-console"))
    {
        Board board(10, 10, 5);
        bool silent = argc > 2 && !strcmp(argv[2], "-silent");
        TextView textView(board, silent);
        textView.doGameCycle();
    }
    else
    {
        std::string name1, name2;
        int h, w, len;
        initscr();
        raw();
        noecho();
        int mode = chooseMode();
        (void)mode;
        move(0, 0);
        endwin();
        if (mode == 0)
        {
            offline(h, w, len, name1, name2);
            move(0, 0);
            endwin();
            Board board(h, w, len);
            ConsolePlayer player1(name1);
            ConsolePlayer player2(name2);
            NcursesView ncursesView(board, player1, player2);
            ncursesView.doGameCycle();
        }
        else if (mode == 1)
        {
            std::string bName, bKey;
            create(h, w, len, name1, bName, bKey);
            move(0, 0);
            endwin();
            ConsolePlayer player1(name1);
            WebPlayer player2(name1, bName, bKey, h, w, len);
            player2.waitJoin();
            Board board(h, w, len);
            NcursesView ncursesView(board, player1, player2);
            ncursesView.doGameCycle();
        }
    }
    return 0;
}