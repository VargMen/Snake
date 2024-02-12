#ifndef BASEMENU_H
#define BASEMENU_H

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

class BaseMenu {
public:
    friend class Menu;

    explicit BaseMenu(const std::vector<std::string>& choices,
                      int startY = 0, int startX = 0,
                      int width = 0, int height = 0);

    //~BaseMenu() { clearWindow(); delwin(m_win); }

    virtual void  start();

protected:

    virtual void setDefault();



    virtual void display() const = 0;

    void clearWindow();

    void updateWidthHeight();



    virtual Event handleInput();

    virtual void handleEvent(const Event& event);

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


#endif //BASEMENU_H
