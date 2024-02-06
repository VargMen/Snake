#include "Menu.hpp"

#include "graphics.hpp"

Menu::Menu(const std::vector<const char*>& choices, int startY, int startX, int width, int height)
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


void Menu::handleInput()
{
    int choice { wgetch(m_win) };
    switch (choice)
    {
        case ERR: return;

        case 'w':
        case KEY_UP:
            if (m_highlight != 0) //We do not allow moving the
                --m_highlight;    //selection outside the list
            break;

        case 's':
        case KEY_DOWN:
            if (m_highlight != 2)
                ++m_highlight;
            break;

        case 10: //10 means KEY_ENTER
            m_currentChoice = m_highlight;

        default: ;
    }
}

void Menu::clearWindow()
{
    clear();
    wclear(m_win);
}

void Menu::updateWidthHeight()
{
    getmaxyx(stdscr, m_height, m_width); //update sizes
    wresize(m_win, m_height, m_width); //make new window
    wclear(m_win);
    wrefresh(m_win);
    box(m_win, 0, 0);
}
