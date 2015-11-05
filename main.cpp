#include <memory>
#include <string>
#include <ncurses.h>
#include "gui/window.hpp"
#include "gui/point.hpp"
#include "gui/screen.hpp"

int main()
{
    gui::screen::init();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    auto main_window = createWindow(gui::Point{0, 0}, gui::screen::width(),
                                    gui::screen::height() - 1);
    main_window->printTo({10, 0}, "left window");
    main_window->refresh();

    auto command_line_window = createWindow(
        gui::Point{0, gui::screen::height() - 1}, gui::screen::width(), 1);
    command_line_window->print("command line");
    command_line_window->refresh();

    auto vertical_split_window = copyWindow(*command_line_window.get());
    // vertical_split_window->resize(30, 1);
    // vertical_split_window->moveTo(1, 1);
    // vertical_split_window->print("copied window");
    // vertical_split_window->refresh();

    auto line_numbers =
        createWindow(gui::Point{0, 0}, 3, gui::screen::height() - 1);

    int ch;
    while ((ch = getch()) != 27)
    {
        switch (ch)
        {
            case KEY_RESIZE:
            {
                erase();

                main_window->clear();
                main_window->moveTo(0, 0);
                main_window->printTo({10, 10}, "some random text");

                command_line_window->clear();
                command_line_window->moveTo(0, gui::screen::height() - 1);
                command_line_window->print("keep this at the bottom");

                // vertical_split_window->clear();
                // vertical_split_window->moveTo(0, 2);
                // vertical_split_window->print("copied window moved");

                refresh();
                main_window->refresh();
                command_line_window->refresh();
                // vertical_split_window->refresh();

                break;
            }
            case KEY_UP:

            {
                main_window->clear();
                main_window->moveTo(0, 0);

                // auto vertical_split_window = copyWindow(*main_window.get());
                auto width = main_window->width() / 2;
                auto height = main_window->height();
                main_window->resize(width, height);
                wborder(main_window->window_, ' ', '|', ' ', ' ', ' ', '@', ' ',
                        ' ');
                main_window->print("width = " +
                                   std::to_string(main_window->width()));
                vertical_split_window->resize(width, height);
                vertical_split_window->moveTo(width + 1, 0);
                vertical_split_window->print(
                    "max width = " + std::to_string(gui::screen::width()));

                refresh();
                main_window->refresh();
                vertical_split_window->refresh();

                break;
            }

            case KEY_DOWN:
            {
                for (auto i = 0; i < main_window->height(); ++i)
                    line_numbers->printTo({0, i}, std::to_string(i + 1));

                main_window->resize(main_window->width() - 3,
                                    main_window->height());
                main_window->move(line_numbers->width(), 0);
                main_window->print("line_numbers width = " +
                                   std::to_string(line_numbers->width()));
                refresh();
                main_window->refresh();
                line_numbers->refresh();
                break;
            }
        }
    }
    line_numbers.release();
    vertical_split_window.release();
    command_line_window.release();
    main_window.release();

    endwin();
    return 0;
};
