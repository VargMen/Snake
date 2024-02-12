#include "PlayerSettingsMenu.hpp"

PlayerSettingsMenu::PlayerSettingsMenu(int playerIndex, const std::vector<std::string>& choices)
            : BaseMenu(choices), m_playerIndex(playerIndex)
{
}

void PlayerSettingsMenu::display() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Player %d", m_playerIndex);

    for (int i{0}; i < m_numOfChoices; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);

        int move_y {m_height/2 + i};
        int move_x {2};
        if(i != Choices::SNAKE_COLOR)
        {
            mvwprintw(m_win, move_y, move_x, "%s: %s", m_choices[i].c_str(), m_choicesValue[i].c_str());
        }
        else
        {
            wattroff(m_win, A_REVERSE);
            mvwprintw(m_win, move_y, move_x + 5, "                 ");

            if (i == m_highlight)
                wattron(m_win, A_REVERSE);

            mvwprintw(m_win, move_y, move_x, "%s: %s", m_choices[i].c_str(), m_colorsStr[colorIndex]);
        }
        wattroff(m_win, A_REVERSE);
    }
}

void PlayerSettingsMenu::changeStringValue(int stringValueIndex, int maxBufferSize)
{
    int move_y { m_height/2 + stringValueIndex };
    int move_x {4 + static_cast<int>(m_choices[stringValueIndex].length()) };

    mvwprintw(m_win, move_y, move_x, "                           "); //Here I erase the previous
    wrefresh(m_win);                                                 //value of the string from the screen
    wmove(m_win, move_y, move_x);//Doing this my next input will be
                                 // printed in place of the previous string value

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
    int cursorX;
    int cursorY;

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
        display();
    }while(!m_saveChanges); //while we are trying to get appropriate value
    m_saveChanges = false;
}

std::vector<std::array<std::string, 5>> PlayerSettingsMenu::parsePlayersSettingFile(const std::string& fileName)
{
    std::fstream playerSettingFile { fileName };

    if (!playerSettingFile.is_open())
        assert(0 && "failed to open playerSettingFile in parsePlayerSettings()");

    std::vector<std::array<std::string, 5>> playerSettings{};
    playerSettings.reserve(5);
    std::string line;
    int pIndex{0};

    while (std::getline(playerSettingFile, line))
    {
        std::string playerLine { "Player  " };
        pIndex += 48; //convert to char

        playerLine[7] = static_cast<char>(pIndex + 1);

        pIndex -= 48; //convert to int

        size_t pSettingsStart { line.find(playerLine) };

        if(pSettingsStart != std::string::npos)
        {
            int settingIndex{};

            while(settingIndex < 4)
            {
                std::getline(playerSettingFile, line);
                size_t colonIndex { line.find(':') };
                if(colonIndex != std::string::npos)
                {
                    std::string data{line.substr(colonIndex + 2)};

                    playerSettings[pIndex][settingIndex] = data;
                }
                else
                {
                    assert(0 && "bad playerSettingFile in parsePlayerSettings()");
                }
                ++settingIndex;
            }
            ++pIndex;
        }
    }

    return playerSettings;
}

void PlayerSettingsMenu::setChoicesValue(const std::array<std::string, 5> values)
{
    for(size_t i{0}; i < values.size(); ++i)
    {
        if(i == 2)
        {
            m_choicesValue[i] = m_colorsStr[stoi(values[i])];
        }
        m_choicesValue[i] = values[i];
    }
}

PlayerSettingsMenu** PlayerSettingsMenu::generatePlSettingsMenus()
{
    std::vector<std::array<std::string, 5>> playerSettings { parsePlayersSettingFile("../playerSettings.txt") };

    PlayerSettingsMenu** plSettingsMenus{};

    for(int i {0}; i < 5; ++i)
    {
        plSettingsMenus[i] = new PlayerSettingsMenu{i, {"Name", "Movement keys", "Snake color", "Snake symbol"} };
        plSettingsMenus[i]->setChoicesValue(playerSettings[i]);
    }

}