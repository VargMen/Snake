#include <cassert>

#include "StartMenu.hpp"

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
    using namespace std::string_literals;

    initNcurses();

    StartMenu m{{"Play"s, "Settings"s, "Exit"s} };

    m.startMenu();

    endNcurses();
    return 0;
}
