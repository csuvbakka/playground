#include <memory>
#include <string>
#include <ncurses.h>
#include "gui/window.hpp"
#include "gui/point.hpp"
#include "gui/screen.hpp"
#include "gui/window_handler.hpp"
#include "gui/command_line.hpp"

int main()
{
    gui::screen::init();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    // auto line_numbers =
    // createWindow(gui::Point{0, 0}, 3, gui::screen::height() - 1);

    WindowHandler handler;
    CommandLine command_line;

    const auto KEY_COLON = 58;

    int ch;
    while ((ch = getch()) != 27)
    {
        switch (ch)
        {
            case KEY_RESIZE:
            {
                erase();

                // command_line_window->clear();
                // command_line_window->moveTo(0, gui::screen::height() - 1);
                // command_line_window->print("keep this at the bottom");

                // refresh();
                // command_line_window->refresh();

                break;
            }
            case KEY_UP:
            {
                handler.vertical_split();
                break;
            }

            case KEY_DOWN:
            {
                // for (auto i = 0; i < handler.active_window()->height(); ++i)
                // line_numbers->printTo({0, i}, std::to_string(i + 1));

                // handler.active_window()->resize(
                // handler.active_window()->width() - 3,
                // handler.active_window()->height());
                // handler.active_window()->move(line_numbers->width(), 0);
                // handler.active_window()->print(
                // "line_numbers width = " +
                // std::to_string(line_numbers->width()));
                // refresh();
                // handler.active_window()->refresh();
                // line_numbers->refresh();
                break;
            }

            case KEY_COLON:
                command_line.read_user_input();
                break;

            default:
                handler.active_window()->printTo({1, 1}, std::to_string(ch));
                handler.active_window()->refresh();
                break;
        }
    }
    return 0;
};
