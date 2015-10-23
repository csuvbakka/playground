#include "window.hpp"
#include <ncurses.h>

namespace gui
{

Window::Window()
    : x_(0)
    , y_(0)
    , width_(0)
    , height_(0)
{
    window_ = newwin(height_, width_, y_, x_);
    wrefresh(window_);
}

Window::Window(int x, int y, int width, int height)
    : x_(x)
    , y_(y)
    , width_(width)
    , height_(height)
{
    window_ = newwin(height_, width_, y_, x_);
    wrefresh(window_);
}

Window::~Window()
{
    wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window_);
    delwin(window_);
}

void Window::moveTo(int x, int y)
{
    wclear(window_);
    mvwin(window_, y, x);
}

void Window::print(const std::string& text)
{
    mvwprintw(window_, 0, 0, text.c_str());
}

void Window::refresh()
{
    wrefresh(window_);
}
};
