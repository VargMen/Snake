#include "BaseMenu.hpp"

#include "graphics.hpp"

BaseMenu::BaseMenu(const std::vector<std::string>& choices, int startY, int startX, int width, int height)
    :m_choices{choices}, m_width{width}, m_height{height}
{
    if(width == 0 && height == 0)
    {
        isResizable = true;
        getmaxyx(stdscr, m_height, m_width);
        m_win = newwin(m_height, m_width, startY, startX);
        box(m_win, 0, 0);
    }
    else
    {
        isResizable = false;
        m_win = newwin(m_height, m_width, startY, startX);
        box(m_win, 0, 0);
    }

    keypad(m_win, TRUE);
    //graphics::initColor();

    //graphics::setMenuColor(m_win);

    m_numOfChoices = static_cast<int>(m_choices.size());
}

void BaseMenu::start()
{
    while(!goBack)
    {
        updateWidthHeight();
        display();
        Event event { handleInput() };
        handleEvent(event);
    }
}


Event BaseMenu::handleInput()
{
    int choice { wgetch(m_win) };
    switch (choice)
    {
        case 'w':
        case KEY_UP:
            if (m_highlight != 0) //We do not allow moving the
                --m_highlight;    //selection outside the list
            break;

        case 's':
        case KEY_DOWN:
            if (m_highlight != m_choices.size() - 1)
                ++m_highlight;
            break;

        case 10: //10 means KEY_ENTER
            return ENTER_PRESSED;

        case 27: //27 means KEY_ESC
            return ESC_PRESSED;
        default: ;
    }

    return max_events;
}

void BaseMenu::clearWindow()
{
    clear();
    wclear(m_win);
}

void BaseMenu::updateWidthHeight()
{
    getmaxyx(stdscr, m_height, m_width); //update sizes
    wresize(m_win, m_height, m_width); //make new window
    wclear(m_win);
    wrefresh(m_win);
    box(m_win, 0, 0);
}

void BaseMenu::setDefault()
{
    m_highlight = 0;
    m_currentChoice = -1;
}

void BaseMenu::handleEvent(const Event& event)
{
}