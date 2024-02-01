#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#include "Game.hpp"
#include "settings.hpp"


constexpr char* snake {   "\n"
                      "                   _____                   _           \n"
                      "                  / ____|                 | |          \n"
                      "                 | (___    _ __     __ _  | | __   ___ \n"
                      "                  \\___ \\  | '_ \\   / _` | | |/ /  / _ \\\n"
                      "                  ____) | | | | | | (_| | |   <  |  __/\n"
                      "                 |_____/  |_| |_|  \\__,_| |_|\\_\\  \\___|\n"
                      "                                       \n"
                      "                                       "
};


class Menu {
public:
    Menu();

    ~Menu();

    void startMenu();

private:

    void makeGame();

    void setDefaultMenu();

    void displayMenu() const;
    void handleInput();

    int m_width{};
    int m_height{};

    const int m_numOfChoices{ settings::numOfMenuChoices };

    WINDOW *m_menuWin{};

    const std::array<const char*, settings::numOfMenuChoices> m_choices
                                        { "Play", "Settings", "Exit"};

    int m_highlight{};

    int m_currentChoice{-1};
};


#endif //MENU_H
