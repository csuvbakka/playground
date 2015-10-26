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
       std::unique_ptr<gui::Window>(new gui::Window(gui::Point{0, 0}, COLS, LINES - 1));
   main_window->printTo({10, 0}, "main stuff");
   main_window->refresh();

   auto window =
       std::unique_ptr<gui::Window>(new gui::Window(gui::Point{0, LINES - 1}, COLS, 1));
   window->print("command line");
   window->refresh();

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

            refresh();
            main_window->refresh();
            window->refresh();
         }
      }
   }
   window.release();
   main_window.release();

   endwin();
   return 0;
};
