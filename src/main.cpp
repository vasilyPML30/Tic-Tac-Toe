#include "Board.h"
#include "BoardView.h"
#include "NcursesView.h"
#include "Player.h"
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

const int version = 1;

static int chooseMode() {
    mvprintw(0, 0, "Welcome to tic-tac-toe! (ver %i)", version);
    mvprintw(1, 0, "Choose game mode:", version);
    mvprintw(3, 0, "Offline game");
    mvprintw(4, 0, "Create game");
    mvprintw(5, 0, "Join game");
    mvprintw(6, 0, "Exit");
    int x = 0, y = 3, ch;
    while (true) {
        move(y, x);
        ch = getch();
        switch (ch) {
        case UP_KEY:
            if (y > 3)
                y--;
            break;
        case DOWN_KEY:
            if (y < 6)
                y++;
            break;
        case ENTER_KEY:
            clear();
            return y - 3;
        }
    }
}

static bool offline(int &h, int &w, int &len, std::string &name1, std::string &name2) {
    std::string data[7] = {"10", "10", "5", "Alice", "Bob"};
    int maxLen[] = {2, 2, 1, 10, 10, 0, 0};
    mvprintw(0, 0, "Board height:");
    mvprintw(1, 0, "Board width:");
    mvprintw(2, 0, "Number to win:");
    mvprintw(3, 0, "First player:");
    mvprintw(4, 0, "Second player:");
    mvprintw(5, 0, "Back");
    mvprintw(6, 0, "Start");
    for (int i = 0; i < 5; i++)
        mvprintw(i, 15, "%s", data[i].c_str());
    int x = 17, y = 0;
    while (true) {
        move(y, x);
        int ch = getch();
        if (ch == UP_KEY && y > 0) {
            y--;
            x = 15 + data[y].length();
        } else if (ch == DOWN_KEY && y < 6) {
            y++;
            x = 15 + data[y].length();
        } else if (ch == ENTER_KEY && y >= 5) {
            clear();
            sscanf(data[0].c_str(), "%i", &h);
            sscanf(data[1].c_str(), "%i", &w);
            sscanf(data[2].c_str(), "%i", &len);
            name1 = data[3];
            name2 = data[4];
            return (y == 6);
        } else if ('a' <= ch && ch <= 'z' && 3 <= y && y <= 4
                 && (int)data[y].length() < maxLen[y]) {
            if ((y == 3 && !data[3].length()) || (y == 4 && !data[4].length()))
                ch += 'A' - 'a';
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        } else if ('0' <= ch && ch <= '9' && y <= 2
                 && (int)data[y].length() < maxLen[y]
                 && (data[y].length() || ch != '0')) {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        } else if (ch == BACKSPACE_KEY && data[y].length()) {
            data[y].pop_back();
            mvprintw(y, --x, " ");
            refresh();
        }
    }   
}

static bool create(int &h, int &w, int &len, std::string &name, std::string &bName, std::string &bKey) {
    std::string data[8] = {"10", "10", "5", "Alice", "stdboard", "123asd"};
    int maxLen[] = {2, 2, 1, 10, 10, 10, 0, 0};
    mvprintw(0, 0, "Board height:");
    mvprintw(1, 0, "Board width:");
    mvprintw(2, 0, "Number to win:");
    mvprintw(3, 0, "Your name:");
    mvprintw(4, 0, "Board name:");
    mvprintw(5, 0, "Board key:");
    mvprintw(6, 0, "Back");
    mvprintw(7, 0, "Start");
    for (int i = 0; i < 6; i++)
        mvprintw(i, 15, "%s", data[i].c_str());
    int x = 17, y = 0;
    while (true) {
        move(y, x);
        int ch = getch();
        if (ch == UP_KEY && y > 0) {
            y--;
            x = 15 + data[y].length();
        } else if (ch == DOWN_KEY && y < 7) {
            y++;
            x = 15 + data[y].length();
        } else if (ch == ENTER_KEY && y >= 6) {
            clear();
            sscanf(data[0].c_str(), "%i", &h);
            sscanf(data[1].c_str(), "%i", &w);
            sscanf(data[2].c_str(), "%i", &len);
            name = data[3];
            bName = data[4];
            bKey = data[5];
            return (y == 7);
        } else if ('a' <= ch && ch <= 'z' && 3 <= y
                && (int)data[y].length() < maxLen[y]) {
            if (y == 3 && !data[3].length())
                ch += 'A' - 'a';
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        } else if ('0' <= ch && ch <= '9' && (y <= 2 || y == 5)
                 && (int)data[y].length() < maxLen[y]
                 && (data[y].length() || ch != '0')) {
            data[y] += ch;
            mvprintw(y, 15, "%s", data[y].c_str());
            x++;
        } else if (ch == BACKSPACE_KEY && data[y].length()) {
            data[y].pop_back();
            mvprintw(y, --x, " ");
            refresh();
        }
    }   
}

static bool join(std::string &name, std::string &bName, std::string &bKey) {
    std::string data[5] = {"Bob", "stdboard", "123asd"};
    int maxLen[] = {10, 10, 10, 0, 0};
    mvprintw(0, 0, "Your name:");
    mvprintw(1, 0, "Board name:");
    mvprintw(2, 0, "Board key:");
    mvprintw(3, 0, "Back");
    mvprintw(4, 0, "Start");
    for (int i = 0; i < 3; i++)
        mvprintw(i, 12, "%s", data[i].c_str());
    int x = 15, y = 0;
    while (true) {
        move(y, x);
        int ch = getch();
        if (ch == UP_KEY && y > 0) {
            y--;
            x = 12 + data[y].length();
        } else if (ch == DOWN_KEY && y < 4) {
            y++;
            x = 12 + data[y].length();
        } else if (ch == ENTER_KEY && y >= 3) {
            clear();
            name = data[0];
            bName = data[1];
            bKey = data[2];
            return (y == 4);
        } else if ('a' <= ch && ch <= 'z' && (int)data[y].length() < maxLen[y]) {
            if (!y && !data[0].length())
                ch += 'A' - 'a';
            data[y] += ch;
            mvprintw(y, 12, "%s", data[y].c_str());
            x++;
        } else if ('0' <= ch && ch <= '9' && y == 2) {
            data[y] += ch;
            mvprintw(y, 12, "%s", data[y].c_str());
            x++;
        } else if (ch == BACKSPACE_KEY && data[y].length()) {
            data[y].pop_back();
            mvprintw(y, --x, " ");
            refresh();
        }
    }   
}

int main(int argc, char **argv) {
    if (argc > 1 && !strcmp(argv[1], "-console")) {
        Board board(10, 10, 5);
        bool silent = argc > 2 && !strcmp(argv[2], "-silent");
        TextView textView(board, silent);
        textView.doGameCycle();
    } else {
        std::string name1, name2;
        int h, w, len;
        while (true) {
            initscr();
            raw();
            noecho();
            keypad(stdscr, TRUE);
            int mode = chooseMode();
            move(0, 0);
            if (mode == 0) {
                if (!offline(h, w, len, name1, name2))
                    continue;
                move(0, 0);
                endwin();
                Board board(h, w, len);
                ConsolePlayer player1(name1);
                ConsolePlayer player2(name2);
                NcursesView ncursesView(board, player1, player2);
                ncursesView.doGameCycle();
            }
            else if (mode == 1) {
                std::string bName, bKey;
                if (!create(h, w, len, name1, bName, bKey))
                    continue;
                move(0, 0);
                endwin();
                ConsolePlayer player1(name1);
                WebPlayer player2(name1, bName, bKey, h, w, len, true);
                if (!player2.waitJoin())
                    continue;
                Board board(h, w, len);
                NcursesView ncursesView(board, player1, player2);
                ncursesView.doGameCycle();
            } else if (mode == 2) {
                std::string bName, bKey;
                if (!join(name2, bName, bKey))
                    continue;
                move(0, 0);
                endwin();
                ConsolePlayer player2(name2);
                WebPlayer player1(name2, bName, bKey, h, w, len, false);
                if (h < 0)
                    continue;
                Board board(h, w, len);
                NcursesView ncursesView(board, player1, player2);
                ncursesView.doGameCycle();
            }
            else {
                move(0, 0);
                endwin();
                break;
            }
        }
    }
    return 0;
}