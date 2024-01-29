#ifndef SETTINGS_H
#define SETTINGS_H

#include <string_view>

namespace setting
{
    constexpr int width{40};
    constexpr int height{21};

    constexpr std::string_view mapPath{ "../Maps/21x40.txt" };

    constexpr int firstPauseTime{250}; //this defines the time for the snake to change position,
                                       //you should specify it in milliseconds.

    constexpr int smallestPauseTime{100};

    constexpr int pauseTimeReduceStep{20};


}
#endif SETTINGS_H
