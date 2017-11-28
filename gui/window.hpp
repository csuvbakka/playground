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
    ~Window();

    std::unique_ptr<Window> clone() const;

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

    static std::unique_ptr<Window> create();
    static std::unique_ptr<Window> create(const Point& p, int width,
                                          int height);

    friend bool operator==(const Window& lhs, const Window& rhs);
    friend bool operator!=(const Window& lhs, const Window& rhs);

private:
    Window();
    Window(const Point& p, int width, int height);
    Window(const Window& other) = delete;
    Window(Window&& other) = default;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = default;
    void initialize_window();

private:
    Point position_;
    int width_;
    int height_;
};

Point window_center(const Window& window);

void draw_right_border(Window& window);

bool operator==(const Window& lhs, const Window& rhs);
bool operator!=(const Window& lhs, const Window& rhs);
};
