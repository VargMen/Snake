#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <vector>

#include "settings.hpp"


class Menu {
public:

    explicit Menu(const std::vector<const char*>& choices,
          int startY = 0, int startX = 0,
          int width = 0, int height = 0);

    virtual void  startMenu() = 0;

protected:

    virtual void setDefaultMenu() = 0;

    virtual void displayMenu() const = 0;

    virtual void handleInput();

    void clearWindow();

    void updateWidthHeight();

protected:
    bool isResizable{};
    int m_width{};
    int m_height{};
    int m_numOfChoices{};
    WINDOW *m_win{};
    std::vector<const char*> m_choices{};
    int m_highlight{};
    int m_currentChoice{-1};
};


#endif //MENU_H
