#pragma once

#include <memory>
#include <vector>

namespace gui
{
class Window;
}

class WindowHandler
{
public:
    WindowHandler();
    ~WindowHandler();

    gui::Window& add_window(std::unique_ptr<gui::Window> window);

    void vertical_split();
    void horizontal_split();
    void close_all_but_active();

    bool is_line_numbering_on();
    void line_numbering_on();
    void line_numbering_off();

    gui::Window* active_window();

    void activate_window(gui::Window& window);

private:
    std::vector<std::unique_ptr<gui::Window>> windows_;
    gui::Window* active_window_;

    bool is_line_numbering_on_;
};
