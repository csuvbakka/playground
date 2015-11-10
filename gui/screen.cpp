#include "screen.hpp"
#include <ncurses.h>

namespace gui
{
Screen::Screen()
{
    initscr();

    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    // attron(COLOR_PAIR(0));

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
    return getmaxx(stdscr);
}

int Screen::height()
{
    return getmaxy(stdscr);
}

void Screen::erase()
{
    ::erase();
}
}
