#include "screen.hpp"
#include <ncurses.h>

namespace gui
{
namespace screen
{
void init()
{
    initscr();
}

int width()
{
    return COLS;
}

int height()
{
    return LINES;
}
}
}
