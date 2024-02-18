#ifndef SETTINGS_H
#define SETTINGS_H

#include <string_view>
#include <array>

namespace settings
{
    constexpr int width{40};
    constexpr int height{21};

    constexpr int bias_x{height/2};

    constexpr int bias_y{width/2 + 37};

    constexpr std::string_view mapPath{ "../Maps/21x40.txt" };

    constexpr int firstPauseTime{250}; //this defines the time for the snake to change position,
                                       //you should specify it in milliseconds.
    constexpr int smallestPauseTime{100};

    constexpr int pauseTimeReduceStep{20};


    constexpr int playerSettingsMenusBias {3};

    constexpr int maxSettingsChoices{3};

    constexpr int maxPlayerSettings{4};

    constexpr int playersAmount {2};

    constexpr std::array<std::string_view, playersAmount> allKeys
    {
        "wsad", //Player 1
        "ikjl", // Player 2
    };

    constexpr std::array<std::string_view, playersAmount> playersNames
    {
        "Sergey", //Player 1
        "Vitya", // Player 2
    };

    constexpr int numOfMenuChoices {3};

}
#endif //SETTINGS_H
