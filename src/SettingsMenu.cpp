#include "SettingsMenu.hpp"


SettingsMenu::SettingsMenu()
{
    m_choices = {"Players amount", "Level", "Difficulty", "Players settings"};

    std::vector<int> choicesValues { parseSettingFile("../settings.txt") };

    assert(choicesValues.size() == m_choices.size() - 1 && "Bad amount of choices values in SettingsMenu()");

    for(const auto& value: choicesValues)
    {
        m_choicesValues.emplace_back(value);
    }
}

std::vector<int> SettingsMenu::parseSettingFile(const std::string& fileName)
{
    std::fstream settingsFile { fileName };

    if (!settingsFile.is_open())
        assert(0 && "failed to open playerSettingFile in parsePlayerSettings()");

    std::vector<int> settingsValues{};
    settingsValues.reserve(settings::maxSettingsChoices);

    std::string line;

    while (std::getline(settingsFile, line))
    {
        size_t colonIndex { line.find(':') };
        if(colonIndex != std::string::npos)
        {
            int value { stoi(line.substr(colonIndex + 2)) };
            settingsValues.emplace_back(value);
        }
    }

    return settingsValues;
}

void SettingsMenu::saveSettingsValues(const std::vector<std::variant<int, std::string>>& values,
                        const char* settingsFilePath)
{
    assert(values.size() == settings::maxSettingsChoices && "Bad amount of values for choices in saveSettingsValues()");

    std::ofstream settingsFile{ settingsFilePath, std::ios::out | std::ios::trunc };

    for(int i{0}; i < settings::maxSettingsChoices; ++i)
    {
        settingsFile << m_choices[i] << ": " << getIntChoiceValue(i) << '\n';
    }
}


Menus SettingsMenu::handleEvent(const Event& event)
{
    switch(event)
    {
        case ENTER_PRESSED:

            m_currentChoice = m_highlight;
            switch(m_currentChoice)
            {
                case Choices::PLAYERS_AMOUNT:
                    handleChangesValue(getIntChoiceValue(PLAYERS_AMOUNT), 1, 96);
                    break;

                case Choices::LEVEL:
                case Choices::DIFFICULTY:
                    handleChangesValue(getIntChoiceValue(m_currentChoice), 1, 8);
                    break;

                case PLAYERS_SETTINGS:
                    return PLAYER_SELECTION_MENU;
                default: ;
            }
            break;

        case ESC_PRESSED:
            saveSettingsValues(m_choicesValues, "../settings.txt");
            return START_MENU;
        default: ;
    }
    return max_menus;
}

void SettingsMenu::handleChangesValue(int& value, int minValue, int maxValue)
{
    do
    {
        changeValue(value, minValue, maxValue);
        display();
    }while(!saveChanges); //while we are trying to get appropriate value
    saveChanges = false;
}

void SettingsMenu::display() const
{
    mvwprintw(m_win, 2, m_width/2 - 4, "Settings");

    int i{0};
    for (; i < m_choices.size() - 1; ++i)
    {
        if (i == m_highlight)
            wattron(m_win, A_REVERSE);


        wmove(m_win, m_height/2, 3);
        mvwprintw(m_win, m_height/2 + i, 2, "%s: %d", m_choices[i].c_str(), getConstIntChoiceValue(i));
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