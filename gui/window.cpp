#include "window.hpp"
#include <ncurses.h>
#include "point.hpp"

namespace gui
{

Window::Window()
    : position_{0, 0}
    , width_{0}
    , height_{0}
{
    initialize_window();
}

Window::Window(const Point& p, int width, int height)
    : position_(p)
    , width_{width}
    , height_{height}
{
    initialize_window();
}

void Window::initialize_window()
{
    window_ = newwin(height_, width_, position_.y, position_.x);
    wrefresh(window_);
}

Window::~Window()
{
    wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    werase(window_);
    wrefresh(window_);
    delwin(window_);
}

std::unique_ptr<Window> Window::clone() const
{
    return Window::create(position_, width_, height_);
}

void Window::move(int x, int y)
{
    position_.x += x;
    position_.y += y;
    // returns ERR if some part of the window would be placed off-screen
    if (mvwin(window_, position_.y, position_.x) == ERR)
        throw 42;
}

void Window::move_to(const Point& pos)
{
    position_.x = pos.x;
    position_.y = pos.y;
    mvwin(window_, pos.y, pos.x);
}

void Window::move_cursor_to(const Point& pos)
{
    wmove(window_, pos.y, pos.x);
}

void Window::resize(int width, int height)
{
    if (width <= 0)
        throw std::runtime_error("Width must be more than zero!");
    if (height <= 0)
        throw std::runtime_error("Height must be more than zero!");
    width_ = width;
    height_ = height;
    wresize(window_, height, width);
}

void Window::print(const std::string& text)
{
    mvwprintw(window_, 0, 0, text.c_str());
}

void Window::print_to(const Point& p, const std::string& text)
{
    mvwprintw(window_, p.y, p.x, text.c_str());
}

void Window::set_border(const std::array<char, 8>& characters)
{
    // 0 - left side
    // 1 - right side
    // 2 - top side
    // 3 - bottom side
    // 4 - top left-hand corner
    // 5 - top right-hand corner
    // 6 - bottom left-hand corner
    // 7 - bottom right-hand corner
    wborder(window_, characters[0], characters[1], characters[2], characters[3],
            characters[4], characters[5], characters[6], characters[7]);
}

void Window::draw_vertical_line_at(const Point& pos, int length, char ch)
{
    mvwvline(window_, pos.y, pos.x, ' ', length);
    ;
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

const Point& Window::position() const
{
    return position_;
}

int Window::width() const
{
    return width_;
}

int Window::height() const
{
    return height_;
}

std::unique_ptr<Window> Window::create()
{
    return std::unique_ptr<Window>(new Window());
}

std::unique_ptr<Window> Window::create(const Point& p, int width, int height)
{
    return std::unique_ptr<Window>(new Window(p, width, height));
}

//------------------------------------------------------------------------------

Point window_center(const Window& window)
{
    return {window.width() / 2, window.height() / 2};
}

void draw_right_border(Window& window)
{
    window.draw_vertical_line_at({0, 0}, window.height(), ' ');
}

bool operator==(const Window& lhs, const Window& rhs)
{
    return lhs.window_ == rhs.window_;
}
bool operator!=(const Window& lhs, const Window& rhs)
{
    return !(lhs == rhs);
}
}
