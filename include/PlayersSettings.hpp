#ifndef PLAYERSSETTINGS_H
#define PLAYERSSETTINGS_H


#include <vector>
#include <string>
#include <cassert>
#include <fstream>

#include "Player.hpp"

#include "settings.hpp"

class PlayersSettings
{
public:

    enum PlayerSettings
    {
        NAME,
        MOVEMENT_KEYS,
        SNAKE_COLOR,
        SNAKE_SYMBOL,

        max_choices
    };

    static std::vector<std::vector<std::string>> parsePlayersSettingFile(const std::string& fileName, int playersAmount);

    static std::vector<Player> generatePLayerSettings(const std::string& fileName, const std::vector<Point>& playersInitPos);

    static bool isSettingsEmpty(const std::vector<std::string>& settings);
};
#endif //PLAYERSSETTINGS_H
