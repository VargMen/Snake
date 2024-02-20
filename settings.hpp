#ifndef SETTINGS_H
#define SETTINGS_H

#include <string_view>
#include <array>

namespace settings
{
    constexpr int width{31};
    constexpr int height{12};

    constexpr int bias_x{0};

    constexpr int bias_y{0};

    constexpr std::string_view mapPath{ "../Maps/12x31.txt" };

    constexpr int firstPauseTime{250}; //this defines the time for the snake to change position,
                                       //you should specify it in milliseconds.
    constexpr int smallestPauseTime{100};

    constexpr int pauseTimeReduceStep{20};


    constexpr int playerSettingsMenusBias {3};

    constexpr int maxSettingsChoices{3};

    constexpr int maxPlayerSettings{4};

    constexpr std::string_view gameSettingsFilePath{ "../settings.txt" };

    constexpr std::string_view playerSettingsFilePath{ "../playersSettings.txt" };

    constexpr int numOfMenuChoices {3};

}
#endif //SETTINGS_H
