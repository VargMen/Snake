#include "Menu.hpp"

#include "graphics.hpp"

Menu::Menu()
{
    initscr();
    noecho();
    curs_set(0);
    cbreak();

    if (has_colors() == FALSE)
    {
        endwin();
        assert(0 && "Your terminal does not support colors");
    }

    start_color();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    m_width = xMax / 2;
    m_height = yMax / 2;

    m_menuWin = newwin(m_height, m_width, m_height / 2, m_width / 2);

    keypad(m_menuWin, TRUE);
    keypad(stdscr, TRUE);

    graphics::initColor();

    graphics::setMenuColor(m_menuWin);

    mvwprintw(m_menuWin, 1, 40, "%s", snake);

    box(m_menuWin, 0, 0);
}

Menu::~Menu()
{
    endwin();
}

void Menu::makeGame()
{
    Game g;
    g.startGame();

    wclear(g.m_winGame);
    wclear(g.m_winScore);

    g.refreshWindow();
}

void Menu::startMenu()
{
    bool isEnd{false};
    while(!isEnd)
    {
        displayMenu();
        handleInput();
        if(m_currentChoice == Choices::Play)
        {
            clear();
            wclear(m_menuWin);
            makeGame();

            setDefaultMenu();
        }
        else if(m_currentChoice == Choices::Exit)
        {
            isEnd = true;
        }
    }
}

void Menu::setDefaultMenu()
{
    m_highlight = 0;
    m_currentChoice = -1;

    mvwprintw(m_menuWin, 1, 40, "%s", snake);

    box(m_menuWin, 0, 0);
}

void Menu::displayMenu() const
{
    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_menuWin, A_REVERSE);

        mvwprintw(m_menuWin, i + m_height / 2 + 2 + 1, m_width / 2 - 2, "%s", m_choices[i]);
        wattroff(m_menuWin, A_REVERSE);
    }
}
void Menu::handleInput()
{
    int choice { wgetch(m_menuWin) };
    switch (choice)
    {
        case 'w':
        case KEY_UP:
            if (m_highlight != 0) //We do not allow moving the
                --m_highlight;    //selection outside the list
            break;

        case 's':
        case KEY_DOWN:
            if (m_highlight != 2)
                ++m_highlight;
            break;

        case 10: //10 means KEY_ENTER
            m_currentChoice = m_highlight;

        default: ;
    }
}
