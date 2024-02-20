#include "PlayersSettings.hpp"

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

std::vector<Player> PlayersSettings::generatePLayerSettings(const std::string& fileName, const std::vector<Point>& playersInitPos)
{
    std::vector<std::vector<std::string>> playersSettingsData { parsePlayersSettingFile(fileName,
                                                   static_cast<int>(playersInitPos.size())) };

    std::vector<Player> playersSettings{};
    std::vector emptySettings {"1", "1", "1", "1"};
    for(size_t i{0}; i < playersSettingsData.size(); ++i)
    {
        if(!isSettingsEmpty(playersSettingsData[i]))
        {
            playersSettings.emplace_back( playersInitPos[i],
                                          Snake::Direction::down,
                                          playersSettingsData[i] );
        }
        else
        {
            return {};
        }
    }

    return playersSettings;
}

bool PlayersSettings::isSettingsEmpty(const std::vector<std::string>& settings)
{
    return settings[MOVEMENT_KEYS] == "1";
}