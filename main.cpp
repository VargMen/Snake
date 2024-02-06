#include <cassert>

#include "MainMenu.hpp"

void initNcurses()
{
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE)
    {
        endwin();
        assert(0 && "Your terminal does not support colors");
    }

    //start_color();
}

void endNcurses()
{
    endwin();
}

int main() {
    initNcurses();

    MainMenu m{ std::vector{"Play", "SettingsMenu", "Exit"} };

    m.startMenu();

    endNcurses();
    return 0;
}
