#include <cassert>

#include "Menu.hpp"
#include "GraphicsSettings.hpp"

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

    start_color();

    GraphicsSettings::initColors();

}

void endNcurses()
{
    endwin();
}

int main() {
    using namespace std::string_literals;

    initNcurses();

    Menu m{};
    m.start();

    endNcurses();
    return 0;
}
