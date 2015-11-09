#include "command_line.hpp"
#include "screen.hpp"
#include "point.hpp"

CommandLine::CommandLine()
    : window_(createWindow(gui::Point{0, gui::screen::height() - 1},
                           gui::screen::width(), 1))
{
    window_->print("command line");
    window_->refresh();
}

std::string CommandLine::read_user_input()
{
    window_->erase();
    window_->refresh();

    window_->printTo({0, 0}, ":");
    auto input = window_->read_user_input_at({1, 0});

    window_->erase();
    window_->refresh();

    return input;
}
