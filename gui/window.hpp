#pragma once

#include <ncurses.h>

#include <array>
#include <memory>
#include <string>

#include "point.hpp"

namespace gui
{

class Window
{

public:
    Window();
    Window(const Point& p, int width, int height);
    Window(const Window& other);
    Window(Window&& other) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    void move(int x, int y);
    void move_to(const Point& pos);
    void move_cursor_to(const Point& pos);

    void resize(int width, int height);
    void print(const std::string& text);
    void print_to(const Point& p, const std::string& text);
    void set_border(const std::array<char, 8>& characters);
    void draw_vertical_line_at(const Point& pos, int length, char ch);

    std::string read_user_input();
    std::string read_user_input_at(const Point& pos);

    void refresh();
    void clear();
    void erase();

    const Point& position() const;
    int width() const;
    int height() const;

    WINDOW* window_;

private:
    void initialize_window();

private:
    Point position_;
    int width_;
    int height_;
};

std::unique_ptr<Window> create_window();
std::unique_ptr<Window> create_window(const Point& p, int width, int height);
std::unique_ptr<Window> copy_window(const Window& window);

Point window_center(const Window& window);

void draw_right_border(Window& window);

};
