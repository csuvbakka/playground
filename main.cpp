#include <memory>
#include <string>
#include <ncurses.h>
#include "gui/window.hpp"

int main()
{
    int ch;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    auto main_window =
        std::make_unique<gui::Window>(gui::Point{0, 0}, COLS, LINES - 1);
    main_window->printTo({10, 0}, "main stuff");
    main_window->refresh();

    auto window =
        std::make_unique<gui::Window>(gui::Point{0, LINES - 1}, COLS, 1);
    window->print("command line");
    window->refresh();

    auto proba = std::make_unique<gui::Window>(*window.get());
    proba->resize(30, 1);
    proba->moveTo(1, 1);
    proba->print("copied window");
    proba->refresh();

    while ((ch = getch()) != 27)
    {
        switch (ch)
        {
            case KEY_RESIZE:
            {
                erase();

                main_window->moveTo(0, 0);
                main_window->printTo({10, 10}, "some random text");

                window->moveTo(0, LINES - 1);
                window->print("keep this at the bottom");

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
