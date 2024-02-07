#include "PlayerSettingsMenu.hpp"

PlayerSettingsMenu::PlayerSettingsMenu(const std::vector<std::string>& choices)
            :Menu(choices)
{
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

void PlayerSettingsMenu::displayMenu() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Player");

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        //mvwprintw(m_win, m_height/2 + i, 2, "%s: 666", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
}

