#include "PlayerSettingsMenu.hpp"

PlayerSettingsMenu::PlayerSettingsMenu(const std::vector<const char *>& choices)
            :Menu(choices)
{
    setDefaultMenu();
    displayMenu();
}

void PlayerSettingsMenu::startMenu()
{
    while(!goBack)
    {
        handleInput();
        updateWidthHeight();
        displayMenu();
    }
}

void PlayerSettingsMenu::handleInput()
{
    int choice { wgetch(m_win) };
    switch (choice)
    {
        case 'w':
        case KEY_UP:
            if (m_highlight != 0) //We do not allow moving the
                --m_highlight;    //selection outside the list
            m_currentChoice = -1;
            break;

        case 's':
        case KEY_DOWN:
            if (m_highlight != 2)
                ++m_highlight;
            m_currentChoice = -1;
            break;

        case 10: //10 means KEY_ENTER
            m_currentChoice = m_highlight;
            break;
        case 27: //27 means KEY_ESC
            goBack = true;
        default: ;
    }
}

void PlayerSettingsMenu::displayMenu() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Player");

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        mvwprintw(m_win, m_height/2 + i, 2, "%s: 666", m_choices[i]);
        wattroff(m_win, A_REVERSE);
    }
}

void PlayerSettingsMenu::setDefaultMenu()
{
    m_highlight = 0;
    m_currentChoice = -1;
}
