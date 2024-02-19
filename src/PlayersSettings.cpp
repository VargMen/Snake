#include "PlayersSettings.hpp"

#include "frequentlyUsedVariables.hpp"

std::vector<std::vector<std::string>> PlayersSettings::parsePlayersSettingFile(const std::string& fileName, int playerAmounts)
{
    std::fstream playerSettingFile { fileName };

    if (!playerSettingFile.is_open())
        assert(0 && "failed to open playerSettingFile in parsePlayerSettings()");

    std::vector<std::vector<std::string>> playerSettings{};

    playerSettings.resize(playerAmounts);

    for(std::size_t i{0}; i < playerAmounts; ++i)
    {
        playerSettings[i].resize(settings::maxPlayerSettings);
    }

    std::string line;
    int pIndex{0};

    while (pIndex < playerAmounts)
    {
        std::getline(playerSettingFile, line);


        std::string playerLine {"Player " + std::to_string(pIndex + 1) + ':'};


        size_t pSettingsStart { line.find(playerLine) };

        if(pSettingsStart != std::string::npos)
        {
            int settingIndex{0};

            while(settingIndex < settings::maxPlayerSettings)
            {
                std::getline(playerSettingFile, line);
                std::size_t colonIndex { line.find(':') };
                if(colonIndex != std::string::npos)
                {
                    std::string data{line.substr(colonIndex + 2)};

                    playerSettings[pIndex][settingIndex] = data;

                } else {
                    assert(0 && "bad playerSettingFile in parsePlayerSettings()");
                }
                ++settingIndex;
            }

        } else {
            for(std::size_t i{0}; i < settings::maxPlayerSettings; ++i)
            {
                playerSettings[pIndex][i] = '1';
            }
        }
        std::getline(playerSettingFile, line);
        ++pIndex;
    }

    return playerSettings;
}

std::vector<Player> PlayersSettings::generatePLayerSettings(const std::string& fileName, int playersAmount)
{
    std::vector<std::vector<std::string>> playersSettingsData { parsePlayersSettingFile(fileName, playersAmount) };

    std::vector<Player> playersSettings{};

    int pos{2};

    for(size_t i{0}; i < playersSettingsData.size(); ++i)
    {
        playersSettings.emplace_back( Point{pos, pos},
                                     Snake::Direction::down,
                                     playersSettingsData[i] );
        pos += 3;
    }

    return playersSettings;
}

int PlayersSettings::getPlayersAmount(const std::string& fileName)
{
    std::fstream settingsFile { fileName };

    if (!settingsFile.is_open())
        assert(0 && "failed to open playerSettingFile in parsePlayerSettings()");

    std::string line{};

    while (std::getline(settingsFile, line))
    {
        size_t playersAmountValueIndex { line.find("Players amount:") };
        if(playersAmountValueIndex != std::string::npos)
        {
            int value { stoi(line.substr(playersAmountValueIndex + 16)) };

            return value;
        }
        else
        {
            assert(0 && "Players amount value not found");
        }
    }
}