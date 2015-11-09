#pragma once

#include <ncurses.h>

#include <array>
#include <memory>
#include <string>

namespace gui
{
struct Point;

class Window
{

public:
    Window();
    Window(const Point& p, int width, int height);
    Window(const Window& other);
    Window(Window&& other) = default;
    Window& operator=(const Window&) = delete;
    ~Window();

    void move(int x, int y);
    void moveTo(int x, int y);
    void move_cursor_to(const Point& pos);

    void resize(int width, int height);
    void print(const std::string& text);
    void printTo(const Point& p, const std::string& text);
    void set_border(const std::array<char, 8>& characters);

    std::string read_user_input();
    std::string read_user_input_at(const Point& pos);

    void refresh();
    void clear();
    void erase();

    int width() const;
    int height() const;

private:
    WINDOW* window_;
    int x_;
    int y_;
    int width_;
    int height_;
};

std::unique_ptr<Window> createWindow();
std::unique_ptr<Window> createWindow(const Point& p, int width, int height);
std::unique_ptr<Window> copyWindow(const Window& window);
};
