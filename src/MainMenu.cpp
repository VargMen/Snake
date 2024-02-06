#include "MainMenu.hpp"

MainMenu::MainMenu(const std::vector<const char *>& choices)
                    :Menu(choices)
{
    displayMenu();
}

void MainMenu::startMenu()
{
    bool isEnd{false};
    while(!isEnd)
    {
        handleInput();
        updateWidthHeight();
        displayMenu();
        if(m_currentChoice == Choices::PLAY)
        {
            makeGame();

            setDefaultMenu();
        }
        else if(m_currentChoice == Choices::SETTINGS)
        {
            clearWindow();

            SettingsMenu settings{std::vector{"Players amount", "Level", "Difficulty"} };
            settings.startMenu();
            setDefaultMenu();
            settings.clearWindow();
            displayMenu();
        }
        else if(m_currentChoice == Choices::EXIT)
        {
            isEnd = true;
        }
    }
}

void MainMenu::setDefaultMenu()
{
    m_highlight = 0;
    m_currentChoice = -1;
}

void MainMenu::makeGame()
{
    Game g;
    g.startGame();

    g.refreshWindow();
}

void MainMenu::displayMenu() const
{
    if(m_width > 54 && m_height > 15)
    {
        wmove(m_win, 3, 10);
        wprintw(m_win, "%s", snake);
    }

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);

        mvwprintw(m_win, m_height/2 + i, 2, "%s", m_choices[i]);
        wattroff(m_win, A_REVERSE);
    }
}
