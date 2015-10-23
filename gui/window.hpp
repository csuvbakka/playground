#pragma once

#include <string>
#include <ncurses.h>

namespace gui
{
class Window
{
public:
    Window();
    Window(int x, int y, int width, int height);
    // TODO: copy ctor, operator=
    ~Window();

    void moveTo(int x, int y);
    void print(const std::string& text);

    void refresh();

private:
    int x_;
    int y_;
    int width_;
    int height_;

    WINDOW* window_;
};
};
