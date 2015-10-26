#pragma once

#include "point.hpp"

#include <ncurses.h>

#include <string>

namespace gui
{
class Window
{
public:
    Window();
    Window(const Point& p, int width, int height);
    // TODO: copy ctor, operator=
    ~Window();

    void moveTo(int x, int y);
    void print(const std::string& text);
    void printTo(const Point& p, const std::string& text);

    void refresh();
    void clear();
    void erase();

private:
    int x_;
    int y_;
    int width_;
    int height_;

    WINDOW* window_;
};
};
