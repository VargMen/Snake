#include "SettingsMenu.hpp"


SettingsMenu::SettingsMenu(const std::vector<std::string>& choices)
        :Menu(choices)
{
    displayMenu();
}

void SettingsMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            m_currentChoice = m_highlight;
            switch(m_currentChoice)
            {
                case Choices::PLAYERS_AMOUNT:
                    handleChangesValue(m_choicesValue[Choices::PLAYERS_AMOUNT], 1, 5);
                    return;

                case Choices::LEVEL:
                    handleChangesValue(m_choicesValue[Choices::LEVEL], 1, 8);
                    return;

                case Choices::DIFFICULTY:
                    handleChangesValue(m_choicesValue[Choices::DIFFICULTY], 1, 8);
                    return;

                case PLAYER_SETTINGS:
                    makePlayersSelectionMenu();
                    return;
                default: ;
            }
            break;

        case ESC_PRESSED:
            goBack = true;
        default: ;
    }
}

void SettingsMenu::makePlayersSelectionMenu()
{
    PlayersSelectionMenu menu{m_choicesValue[Choices::PLAYERS_AMOUNT], m_height/2 + 4, 18};
    menu.startMenu();
}
void SettingsMenu::startMenu()
{
    while(!goBack)
    {
        updateWidthHeight();
        displayMenu();
        Event event { handleInput() };
        handleEvent(event);
    }
}

void SettingsMenu::handleChangesValue(int& value, int minValue, int maxValue)
{
    do
    {
        changeValue(value, minValue, maxValue);
        displayMenu();
    }while(!saveChanges); //while we are trying to get appropriate value
    saveChanges = false;
}

void SettingsMenu::displayMenu() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Settings");

    int i{0};
    for (; i < m_numOfChoices - 1; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        mvwprintw(m_win, m_height/2 + i, 2, "%s: %d", m_choices[i].c_str(), m_choicesValue[i]);
        wattroff(m_win, A_REVERSE);
    }

    if (i == m_highlight)
        wattron(m_win, A_REVERSE);
    mvwprintw(m_win, m_height/2 + i + 2, 2, "%s", m_choices[i].c_str());
    wattroff(m_win, A_REVERSE);
}

void SettingsMenu::changeValue(int& value, int minValue, int maxValue)
{
    int choice { wgetch(m_win) };
    switch (choice)
    {
        case 's':
        case KEY_DOWN:
            if (value != minValue)
                --value;
            break;

        case 'w':
        case KEY_UP:
            if (value != maxValue)
                ++value;
            break;

        case 10: //10 means KEY_ENTER
            saveChanges = true;
            break;

        case 27: //27 means KEY_ESC
            goBack = true;
        default: ;
    }
}