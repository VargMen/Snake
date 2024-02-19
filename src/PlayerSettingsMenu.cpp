#include "PlayerSettingsMenu.hpp"

#include "PlayersSettings.hpp"

int PlayerSettingsMenu::m_playersAmount = 1;
bool PlayerSettingsMenu::m_isSettingSaved = false;
const char* PlayerSettingsMenu::m_playerSettingsFilePath = "../playersSettings.txt";

PlayerSettingsMenu::PlayerSettingsMenu(int playerIndex)
            : m_playerIndex(playerIndex)
{
    m_choices = {"Name", "Movement keys", "Snake color", "Snake symbol"};
}

PlayerSettingsMenu::~PlayerSettingsMenu()
{
    if(!m_isSettingSaved)
    {
        m_isSettingSaved = true;
    }
}

void PlayerSettingsMenu::display() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Player %d", m_playerIndex);

    for (int i{0}; i < m_choices.size(); ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);

        int move_y {m_height/2 + i};
        int move_x {2};

        if(i != PlayersSettings::SNAKE_COLOR)
        {
            mvwprintw(m_win, move_y, move_x, "%s: %s", m_choices[i].c_str(), getConstStrChoiceValue(i).c_str());
        }
        else
        {
            wattroff(m_win, A_REVERSE);
            mvwprintw(m_win, move_y, move_x + 5, "                         ");

            if (i == m_highlight)
                wattron(m_win, A_REVERSE);

            mvwprintw(m_win, move_y, move_x, "%s: %s", m_choices[i].c_str(), m_colorsStr[m_colorIndex]);
        }
        wattroff(m_win, A_REVERSE);
    }
}

void PlayerSettingsMenu::changeStringValue(int stringValueIndex, int maxBufferSize)
{
    int move_y { m_height/2 + stringValueIndex };
    int move_x {4 + static_cast<int>(m_choices[stringValueIndex].length()) };

    mvwprintw(m_win, move_y, move_x, "                           "); // Here I erase the previous
    wrefresh(m_win);                                                 // value of the string from the screen
    wmove(m_win, move_y, move_x);// Doing this my next input will be
                                 // printed in place of the previous string value

    getStrChoiceValue(stringValueIndex) = getInputStr(maxBufferSize);
}

Menus PlayerSettingsMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:
            m_currentChoice = m_highlight;
            switch(m_currentChoice)
            {
                case PlayersSettings::NAME:
                    handleChangesStringValue(PlayersSettings::NAME, 31);
                    break;

                case PlayersSettings::MOVEMENT_KEYS:
                    handleChangesStringValue(PlayersSettings::MOVEMENT_KEYS, 4);
                    break;

                case PlayersSettings::SNAKE_COLOR:
                    handleChangesValue(m_colorIndex, GREEN, MAGENTA);
                    break;
                case PlayersSettings::SNAKE_SYMBOL:
                    handleChangesStringValue(PlayersSettings::SNAKE_SYMBOL, 1);
                    break;
            }
            break;

        case ESC_PRESSED:
            return PLAYER_SELECTION_MENU;
        default: ;
    }
    return max_menus;
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
        if(ch == 10 && i == 0) // if we don't write any characters and just press enter
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

    return getStrChoiceValue(m_highlight);
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

int PlayerSettingsMenu::getIndexValue(int index) const
{
    return m_colorIndex;
}

void PlayerSettingsMenu::setChoicesValue(const std::vector<std::string>& values)
{
    for(size_t i{0}; i < settings::maxPlayerSettings; ++i)
    {
        if(i == 2)
        {
            m_choicesValues.emplace_back(m_colorsStr[std::stoi(values[i])] ); //write color as a string
            m_colorIndex = std::stoi(values[i]);
            continue;
        }

        m_choicesValues.emplace_back(values[i]);
    }
}

PlayerSettingsMenu** PlayerSettingsMenu::generatePlSettingsMenus(int playersAmount)
{
    PlayerSettingsMenu::setPlayersAmount(playersAmount);

    std::vector<std::vector<std::string>> playerSettings { PlayersSettings::parsePlayersSettingFile(m_playerSettingsFilePath, m_playersAmount) };

    PlayerSettingsMenu** plSettingsMenus{ new PlayerSettingsMenu*[m_playersAmount]{} };

    for(int i {0}; i < m_playersAmount; ++i)
    {
        plSettingsMenus[i] = new PlayerSettingsMenu{i + 1};
        plSettingsMenus[i]->setChoicesValue(playerSettings[i]);
    }

    return plSettingsMenus;
}