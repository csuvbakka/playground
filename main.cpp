// #include <string.h>
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

   printw("Press F1 to exit");
   refresh();

   auto window =
       std::unique_ptr<gui::Window>(new gui::Window(0, LINES - 1, COLS, 1));
   window->print("command line");
   window->refresh();

   while ((ch = getch()) != 27)
   {
      switch (ch)
      {
         case KEY_RESIZE:
         {
            clear();
            mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
            for (int i = 0; i < COLS; i++)
               mvaddch(1, i, '*');
            refresh();

            window->moveTo(0, LINES - 1);
            window->print("keep this at the bottom");
            window->refresh();
         }
      }
   }
   window.release();

   endwin();
   return 0;
};
