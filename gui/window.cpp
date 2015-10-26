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

Window::Window(const Window& other)
    : x_(other.x_)
    , y_(other.y_)
    , width_(other.width_)
    , height_(other.height_)
{
    window_ = newwin(height_, width_, y_, x_);
}

Window::Window(const Point& p, int width, int height)
    : x_(p.x)
    , y_(p.y)
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
    x_ = x;
    y_ = y;
    mvwin(window_, y, x);
}

void Window::resize(int width, int height)
{
    width_ = width;
    height_ = height;
    wresize(window_, height, width);
}

void Window::print(const std::string& text)
{
    mvwprintw(window_, 0, 0, text.c_str());
}

void Window::printTo(const Point& p, const std::string& text)
{
    mvwprintw(window_, p.y, p.x, text.c_str());
}

void Window::refresh()
{
    wrefresh(window_);
}

void Window::clear()
{
    wclear(window_);
}

void Window::erase()
{
    werase(window_);
}
};
