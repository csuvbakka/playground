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
    main_window->printTo({10, 0}, "main stuff");
    main_window->refresh();

    auto window = createWindow(gui::Point{0, gui::screen::height() - 1},
                               gui::screen::width(), 1);
    window->print("command line");
    window->refresh();

    auto proba = copyWindow(*window.get());
    proba->resize(30, 1);
    proba->moveTo(1, 1);
    proba->print("copied window");
    proba->refresh();

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

                window->clear();
                window->moveTo(0, gui::screen::height() - 1);
                window->print("keep this at the bottom");

                proba->clear();
                proba->moveTo(0, 2);
                proba->print("copied window moved");

                refresh();
                main_window->refresh();
                window->refresh();
                proba->refresh();
            }
        }
    }
    proba.release();
    window.release();
    main_window.release();

    endwin();
    return 0;
};
