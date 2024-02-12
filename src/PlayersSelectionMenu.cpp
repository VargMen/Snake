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

PlayersSelectionMenu::PlayersSelectionMenu()
        : BaseMenu {generateChoices(5) }
{
}

void PlayersSelectionMenu::display() const
{
    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        mvwprintw(m_win, i + 1, 1, "%s", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
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
