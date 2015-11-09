#include "window_handler.hpp"
#include "../gui/window.hpp"
#include "../gui/point.hpp"
#include "../gui/screen.hpp"

WindowHandler::WindowHandler()
{
    windows_.push_back(createWindow(gui::Point{0, 0}, gui::screen::width(),
                                    gui::screen::height() - 1));
    active_window_ = windows_.front().get();
    active_window_->refresh();
}

WindowHandler::~WindowHandler()
{
    for (auto i = windows_.rbegin(); i != windows_.rend(); ++i)
        i->release();

    endwin();
}

void WindowHandler::vertical_split()
{
    auto vertical_split_window = copyWindow(*active_window_);

    auto width = active_window_->width() / 2;
    auto height = active_window_->height();
    active_window_->resize(width, height);
    active_window_->set_border({{' ', '|', ' ', ' ', ' ', '@', ' ', ' '}});
    active_window_->print("width = " + std::to_string(active_window_->width()));

    vertical_split_window->resize(width, height);
    vertical_split_window->moveTo(width + 1, 0);
    vertical_split_window->print("max width = " +
                                 std::to_string(gui::screen::width()));

    active_window_->refresh();
    vertical_split_window->refresh();

    windows_.push_back(std::move(vertical_split_window));
}

gui::Window* WindowHandler::active_window()
{
    return active_window_;
}
