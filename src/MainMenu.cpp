#include "MainMenu.hpp"

using namespace std::string_literals;


MainMenu::MainMenu(const std::vector<std::string>& choices)
                    :Menu(choices)
{
    displayMenu();
}

void MainMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            m_currentChoice = m_highlight;
            switch(m_currentChoice)
            {
                case Choices::PLAY:
                    makeGame();
                    setDefaultMenu();
                    return;

                case Choices::SETTINGS:
                    makeSettings();
                    setDefaultMenu();
                    return;

                case Choices::EXIT:
                    abort();
                default: ;
            }
           break;
        case ESC_PRESSED:

        default: ;
    }
}

void MainMenu::startMenu()
{
    while(1)
    {
        updateWidthHeight();
        displayMenu();
        Event event { handleInput() };
        handleEvent(event);
    }
}

void MainMenu::makeSettings()
{
    SettingsMenu settings{ {"Players amount", "Level", "Difficulty", "Players settings"} };
    settings.startMenu();
    settings.clearWindow();
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

        mvwprintw(m_win, m_height/2 + i, 2, "%s", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
}
