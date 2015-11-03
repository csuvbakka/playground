#pragma once

#include <ncurses.h>

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
    Window& operator=(const Window&) = delete;
    ~Window();

    void moveTo(int x, int y);
    void resize(int width, int height);
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

std::unique_ptr<Window> createWindow();
std::unique_ptr<Window> createWindow(const Point& p, int width, int height);
std::unique_ptr<Window> copyWindow(const Window& window);
};
