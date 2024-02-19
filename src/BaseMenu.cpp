#include "BaseMenu.hpp"

BaseMenu::BaseMenu()
{
    getmaxyx(stdscr, m_height, m_width);
    m_win = newwin(m_height, m_width, 0, 0);
    box(m_win, 0, 0);

    GraphicsSettings::setTheme(m_win, GraphicsSettings::m_currentColorPair);

    keypad(m_win, TRUE);
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

void BaseMenu::applyTheme(short themeIndex)
{
    GraphicsSettings::setTheme(m_win, themeIndex);
}

int& BaseMenu::getIntChoiceValue(int index)
{
    return std::get<int>(m_choicesValues[index]);
}

int BaseMenu::getConstIntChoiceValue(int index) const
{
    return std::get<int>(m_choicesValues[index]);
}

std::string& BaseMenu::getStrChoiceValue(int index)
{
    return std::get<std::string>(m_choicesValues[index]);
}

std::string BaseMenu::getConstStrChoiceValue(int index) const
{
    return std::get<std::string>(m_choicesValues[index]);
}