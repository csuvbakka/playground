#include "screen.hpp"
#include <ncurses.h>

namespace gui
{
Screen::Screen()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();
}

Screen::~Screen()
{
    endwin();
}

int Screen::width()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    return x;
}

int Screen::height()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

void Screen::erase()
{
    ::erase();
}
}
