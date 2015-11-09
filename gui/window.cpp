#include "window.hpp"
#include "point.hpp"
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

void Window::move(int x, int y)
{
    x_ += x;
    y_ += y;
    mvwin(window_, y, x);
}

void Window::moveTo(int x, int y)
{
    x_ = x;
    y_ = y;
    mvwin(window_, y, x);
}

void Window::move_cursor_to(const Point& pos)
{
    wmove(window_, pos.y, pos.x);
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

void Window::set_border(const std::array<char, 8>& characters)
{
    wborder(window_, characters[0], characters[1], characters[2], characters[3],
            characters[4], characters[5], characters[6], characters[7]);
}

std::string Window::read_user_input()
{
    std::array<char, 255> buffer;
    wgetnstr(window_, buffer.data(), 255);
    return std::string(buffer.data());
}

std::string Window::read_user_input_at(const Point& pos)
{
    move_cursor_to(pos);
    return read_user_input();
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

int Window::width() const
{
    return width_;
}

int Window::height() const
{
    return height_;
}
//------------------------------------------------------------------------------

std::unique_ptr<Window> createWindow()
{
    return std::make_unique<Window>();
}

std::unique_ptr<Window> createWindow(const Point& p, int width, int height)
{
    return std::make_unique<Window>(p, width, height);
}

std::unique_ptr<Window> copyWindow(const Window& window)
{
    return std::make_unique<Window>(window);
}
};
