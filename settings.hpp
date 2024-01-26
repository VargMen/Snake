#ifndef SETTINGS_H
#define SETTINGS_H

#include <string_view>

namespace setting
{
    constexpr int width{31};
    constexpr int height{12};

    constexpr std::string_view mapPath{ "../Maps/12x31.txt" };

    constexpr int firstPauseTime{300}; //this defines the time for the snake to change position,
                                       //you should specify it in milliseconds.

    constexpr int smallestPauseTime{100};

    constexpr int pauseTimeReduceStep{20};


}
#endif SETTINGS_H
