#include "SettingsMenu.hpp"


SettingsMenu::SettingsMenu(const std::vector<const char *>& choices)
        :Menu(choices)
{
    setDefaultMenu();
    displayMenu();
}


void SettingsMenu::startMenu()
{
    while(!goBack)
    {
        handleInput();
        updateWidthHeight();
        displayMenu();

        if(m_currentChoice == Choices::PLAYERS_AMOUNT)
        {
            handleChangesValue(m_choicesValue[Choices::PLAYERS_AMOUNT], 1, 5);
            PlayersSettingsChoiceMenu menu{m_choicesValue[0], m_height / 2 - 1, 19};
            menu.startMenu();
        }
        else if(m_currentChoice == Choices::LEVEL)
        {
            handleChangesValue(m_choicesValue[Choices::LEVEL], 1, 8);
        }
        else if(m_currentChoice == Choices::DIFFICULTY)
        {
            handleChangesValue(m_choicesValue[Choices::DIFFICULTY], 1, 8);
        }
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
    mvwprintw(m_win, 2, m_width/2 - 4, "SettingsMenu");

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        mvwprintw(m_win, m_height/2 + i, 2, "%s: %d", m_choices[i], m_choicesValue[i]);
        wattroff(m_win, A_REVERSE);
    }
}

void SettingsMenu::handleInput()
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

void SettingsMenu::setDefaultMenu()
{
    m_highlight = 0;
    m_currentChoice = -1;
}