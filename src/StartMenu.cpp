#include "StartMenu.hpp"

using namespace std::string_literals;


StartMenu::StartMenu()
{
    m_choices = {"Play", "Settings", "Exit"};
}

Menus StartMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            m_currentChoice = m_highlight;

            switch(m_currentChoice)
            {
                case Choices::PLAY:
                    if(!makeGame())
                    {
                        mvwprintw(m_win, m_height/2, m_width/2 - 35, "Please specify the settings for each player");
                        wgetch(m_win);
                    }
                    setDefault();
                    return max_menus;

                case Choices::SETTINGS:
                    return SETTINGS_MENU;

                case Choices::EXIT:
                    goBack = true;
                default: ;
            }
           break;
        case ESC_PRESSED:
            goBack = true;
        default: ;
    }
    return max_menus;
}

bool StartMenu::makeGame()
{
    Game g;
    if(g.isGameSet)
    {
        g.startGame();

        g.refreshWindow();

        return true;
    }
    else
    {
        return false;
    }
}


void StartMenu::display() const
{
    if(m_width > 54 && m_height > 15)
    {
        wmove(m_win, 3, 10);
        wprintw(m_win, "%s", snake);
    }

    for (int i{0}; i < m_choices.size(); ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);

        mvwprintw(m_win, m_height/2 + i, 2, "%s", m_choices[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
}
