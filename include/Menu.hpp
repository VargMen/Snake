#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <vector>
#include <string>

#include "settings.hpp"

enum Event
{
    ENTER_PRESSED,
    ESC_PRESSED,
    SPACE_PRESSED,

    max_events
};

class Menu {
public:

    explicit Menu(const std::vector<std::string>& choices,
          int startY = 0, int startX = 0,
          int width = 0, int height = 0);

    virtual void  startMenu() = 0;

protected:

    virtual void setDefaultMenu();

    virtual void displayMenu() const = 0;

    virtual Event handleInput();

    virtual void handleEvent(const Event& event);

    void clearWindow();

    void updateWidthHeight();

protected:
    bool isResizable{};
    bool goBack{};
    int m_width{};
    int m_height{};
    int m_numOfChoices{};
    WINDOW *m_win{};
    std::vector<std::string> m_choices{};
    int m_highlight{};
    int m_currentChoice{-1};
};


#endif //MENU_H
