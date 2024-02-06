#include "PlayersSettingsChoiceMenu.hpp"
#include "PlayerSettingsMenu.hpp"
#include "string"

std::vector<const char*> PlayersSettingsChoiceMenu::generateChoices(int playersAmount)
{
    std::vector<const char*> choices{};
    std::string player { "Player  "};
    for(int i{1}; i <= playersAmount; ++i)
    {
        player[7] = static_cast<char>(i);
        choices.push_back(player.c_str());
    }
    return choices;
}

PlayersSettingsChoiceMenu::PlayersSettingsChoiceMenu(int playerAmounts, int startY,
                                                     int startX)
                           : Menu{{"Player 1", "Player 2", "Player 3"},
                                  startY, startX, 10, playerAmounts + 2}
{
    setDefaultMenu();
    displayMenu();
}

void PlayersSettingsChoiceMenu::displayMenu() const
{
    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        mvwprintw(m_win, i + 1, 1, "%s", m_choices[i]);
        wattroff(m_win, A_REVERSE);
    }
}

void PlayersSettingsChoiceMenu::setDefaultMenu()
{
    m_highlight = 0;
    m_currentChoice = -1;
}

void PlayersSettingsChoiceMenu::handleInput()
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
void PlayersSettingsChoiceMenu::startMenu()
{
    while(!goBack)
    {
        displayMenu();
        handleInput();

        for(int i{1}; i <= m_numOfChoices; ++i)
        if(m_currentChoice == i)
        {
            PlayerSettingsMenu p{}
        }
    }

    clearWindow();
    wrefresh(m_win);
    delwin(m_win);
}
