#include "PlayersSelectionMenu.hpp"
#include "string"


std::vector<std::string> PlayersSelectionMenu::generateChoices(int playersAmount)
{
    std::vector<std::string> players{};

    for (int i = 1; i <= playersAmount; ++i) {
        players.push_back("Player " + std::to_string(i));
    }

    return players;
}

PlayersSelectionMenu::PlayersSelectionMenu(int playersAmount)
{
    m_choices = generateChoices(playersAmount);
}

void PlayersSelectionMenu::display() const
{
    int column {1};
    int line {1};

    int maxLines {32};

    for (int i{0}; i < m_choices.size(); ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);

        if( !(i % maxLines) && i )
        {
            line = 1;
            column += 12;
        }

        mvwprintw(m_win, line, column, "%s", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);

        ++line;
    }
}

Menus PlayersSelectionMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            return static_cast<Menus>(m_highlight + 3); //in the Menus enum the menu for the player starts at index 3,
        case ESC_PRESSED:                               //so we have to add bias to get the appropriate player settings menu
            return SETTINGS_MENU;
        default: ;
    }
    return max_menus;
}
