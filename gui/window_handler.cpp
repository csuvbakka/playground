#include "window_handler.hpp"
#include "../gui/window.hpp"
#include "../gui/point.hpp"
#include "../gui/screen.hpp"

#include <algorithm>

WindowHandler::WindowHandler()
{
    windows_.push_back(create_window(gui::Point{0, 0}, gui::Screen::width(),
                                     gui::Screen::height() - 1));
    active_window_ = windows_.front().get();
    active_window_->refresh();
}

WindowHandler::~WindowHandler()
{
    for (auto i = windows_.rbegin(); i != windows_.rend(); ++i)
        i->release();
}

void WindowHandler::vertical_split()
{
    auto width = active_window_->width() / 2;

    if (width < 4)
        return;

    auto height = active_window_->height();
    auto vertical_split_window = copy_window(*active_window_);

    active_window_->resize(width, height);
    // active_window_->set_border({{' ', '|', ' ', ' ', ' ', '@', ' ', ' '}});
    // active_window_->set_border({{'@', '@', '@', '@', '@', '@', '@', '@'}});
    active_window_->print_to(window_center(*active_window_),
                             std::to_string(active_window_->width()));

    vertical_split_window->resize(vertical_split_window->width() - width - 1,
                                  height);
    vertical_split_window->move_to({width + 1, 0});
    // vertical_split_window->set_border(
    // {{'/', '/', '/', '/', '/', '/', '/', '/'}});
    vertical_split_window->print_to(
        window_center(*vertical_split_window.get()),
        std::to_string(vertical_split_window->width()));

    wattron(vertical_split_window->window_, COLOR_PAIR(2));
    draw_right_border(*vertical_split_window.get());
    wattroff(vertical_split_window->window_, COLOR_PAIR(2));

    // wattrset(active_window_->window_, 0);
    // wattrset(vertical_split_window->window_, 0);

    vertical_split_window->refresh();
    active_window_->refresh();

    windows_.push_back(std::move(vertical_split_window));
}

void WindowHandler::horizontal_split()
{
    auto height = active_window_->height() / 2;

    if (height < 3)
        return;

    auto width = active_window_->width();
    auto horizontal_split_window = copy_window(*active_window_);

    active_window_->resize(width, height);
    active_window_->set_border({{'-', '-', '-', '-', '-', '-', '-', '-'}});

    active_window_->print_to(window_center(*active_window_),
                             std::to_string(active_window_->height()));

    horizontal_split_window->resize(width,
                                    horizontal_split_window->height() - height);
    horizontal_split_window->move_to(
        {horizontal_split_window->position().x, height});
    horizontal_split_window->set_border(
        {{'-', '-', '-', '-', '-', '-', '-', '-'}});
    horizontal_split_window->print_to(
        window_center(*horizontal_split_window.get()),
        std::to_string(horizontal_split_window->height()));

    horizontal_split_window->refresh();
    active_window_->refresh();

    windows_.push_back(std::move(horizontal_split_window));
}

void WindowHandler::close_all_but_active()
{
    if (windows_.size() <= 1)
        return;

    // gui::Screen::erase();

    auto active =
        std::find_if(windows_.begin(), windows_.end(),
                     [this](const std::unique_ptr<gui::Window>& window)
                     {
                         return window.get() == active_window_;
                     });

    std::iter_swap(windows_.begin(), active);
    windows_.resize(1);
    active_window_ = windows_.front().get();

    active_window_->erase();
    active_window_->resize(gui::Screen::width(), gui::Screen::height() - 1);
    active_window_->move_to({0, 0});
    active_window_->set_border({{'+', '+', '+', '+', '+', '+', '+', '+'}});
    active_window_->print_to(gui::window_center(*active_window_),
                             "only one can remain");
    active_window_->refresh();
}

gui::Window* WindowHandler::active_window()
{
    return active_window_;
}
