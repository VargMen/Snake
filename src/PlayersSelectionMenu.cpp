#include "PlayersSelectionMenu.hpp"
#include "string"


std::vector<std::string> PlayersSelectionMenu::generateChoices(int playersAmount)
{
    std::vector<std::string> players{};
    std::string player{ "PLayer  "};
    for(int i{1}; i <= playersAmount; ++i)
    {
        i += 48; //convert to char

        player[7] = static_cast<char>(i);

        i -= 48; //convert to int

        players.push_back(player);
    }

    return players;
}

PlayersSelectionMenu::PlayersSelectionMenu(int playerAmounts, int startY,
                                           int startX)
                           : Menu{ {generateChoices(playerAmounts) },
                                  startY, startX, 10, playerAmounts + 2}
{
    displayMenu();
}

void PlayersSelectionMenu::displayMenu() const
{
    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        mvwprintw(m_win, i + 1, 1, "%s", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
}

void PlayersSelectionMenu::startMenu()
{
    while(!goBack)
    {
        displayMenu();
        Event event { handleInput() };

        handleEvent(event);
    }

    clearWindow();
    wrefresh(m_win);
    delwin(m_win);
}

void PlayersSelectionMenu::makePlayerSettingsMenu(int playerIndex)
{
    PlayerSettingsMenu menu{m_currentChoice, {"Name", "Movement keys", "Snake symbol", "Snake color"}};
    menu.startMenu();
}

void PlayersSelectionMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            makePlayerSettingsMenu(m_highlight);

        case ESC_PRESSED:
            goBack = true;
        default: ;
    }
}