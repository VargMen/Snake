#include "PlayerSettingsMenu.hpp"

PlayerSettingsMenu::PlayerSettingsMenu(int playerIndex, const std::vector<std::string>& choices)
            :Menu(choices), m_playerIndex(playerIndex)
{
    displayMenu();
}

void PlayerSettingsMenu::startMenu()
{
    while(!goBack)
    {
        updateWidthHeight();
        displayMenu();
        Event event { handleInput() };
        handleEvent(event);
    }
}

void PlayerSettingsMenu::displayMenu() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Player");

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        mvwprintw(m_win, m_height/2 + i, 2, "%s: %s", m_choices[i].c_str(), m_choicesValue[i].c_str());
        wattroff(m_win, A_REVERSE);
    }
}

void PlayerSettingsMenu::changeStringValue(int stringValueIndex, int maxBufferSize)
{
    mvwprintw(m_win, m_height/2 + stringValueIndex, 4 + m_choices[stringValueIndex].length(), "                           "); //Here I erase the previous
    wrefresh(m_win);                                                                                                          //value of the string from the screen
    wmove(m_win, m_height/2 + stringValueIndex, 4 + m_choices[stringValueIndex].length()); //Doing this my next input will be
    move(m_height/2 + stringValueIndex, 4 + m_choices[stringValueIndex].length());         //printed in place of the previous string value

    m_choicesValue[stringValueIndex] = getInputStr(maxBufferSize);
}

void PlayerSettingsMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            m_currentChoice = m_highlight;
            switch(m_currentChoice)
            {
                case Choices::NAME:
                    handleChangesStringValue(NAME, 31);
                    break;

                case Choices::MOVEMENT_KEYS:
                    handleChangesStringValue(MOVEMENT_KEYS, 4);
                    break;

                case Choices::SNAKE_COLOR:
                    handleChangesValue(colorIndex, GREEN, MAGENTA);
                    break;
                case Choices::SNAKE_SYMBOL:
                    handleChangesStringValue(SNAKE_SYMBOL, 1);
                    break;
            }
            break;

        case ESC_PRESSED:
            goBack = true;
        default: ;
    }
}

std::string PlayerSettingsMenu::getInputStr(int bufferSize)
{
    char* buffer = new char[bufferSize + 1];

    int ch;
    int i{0};
    int cursorX{};
    int cursorY{};

    while((ch = wgetch(m_win)) != 27)
    {
        if(ch == 10 && i == 0) //if we don't write any characters and just press enter
            break;

        if(ch == KEY_BACKSPACE)
        {
            getyx(m_win, cursorY, cursorX);
            if(i > 0)
            {
                --i;

                wmove(m_win, cursorY, cursorX - 1);// Move the cursor back on the screen

                waddch(m_win, ' ');// Print a space to visually erase the character

                wmove(m_win, cursorY, cursorX - 1);// Move the cursor back again

                wrefresh(m_win);// Refresh the window to update the display
            }
            continue;
        }

        if(ch == ' ' || ch == 10 || i >= bufferSize)
        {
            buffer[i] = '\0';

            std::string result {buffer};

            delete[] buffer;

            return result;
        }

        buffer[i] = static_cast<char>(ch);
        ++i;
        waddch(m_win, ch);
    }

    return m_choicesValue[m_highlight];
}

void PlayerSettingsMenu::changeValue(int& value, int minValue, int maxValue)
{
    int choice{wgetch(m_win)};
    switch (choice) {
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
            m_saveChanges = true;
            break;

        case 27: //27 means KEY_ESC
            goBack = true;
        default:;
    }
}

void PlayerSettingsMenu::handleChangesStringValue(int stringValueIndex, int maxStrSize)
{
    changeStringValue(stringValueIndex, maxStrSize);
}

void PlayerSettingsMenu::handleChangesValue(int& choice, int minValue, int maxValue)
{
    do
    {
        changeValue(choice, minValue, maxValue);
        displayMenu();
    }while(!m_saveChanges); //while we are trying to get appropriate value
    m_saveChanges = false;
}