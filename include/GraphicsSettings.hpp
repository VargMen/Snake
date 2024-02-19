#ifndef GRAPHICSSETTINGS_HPP
#define GRAPHICSSETTINGS_HPP

#include <vector>
#include <string>
#include <ncurses.h>
#include <utility>

#include "Player.hpp"

class GraphicsSettings
{
public:
    enum Colors
    {
        GREEN,
        BLUE,
        RED,
        YELLOW,
        GRAY,
        ORANGE,
        WHITE,
        BLACK,
        CYAN,
        MAGENTA,

        max_snake_colors
    };

    enum MyColors
    {
        MyCOLOR_ORANGE = 10,
        MyCOLOR_GRAY,
        MyCOLOR_GREEN,
        MyCOLOR_YELLOW,
        MyCOLOR_RED,
        MyCOLOR_BLUE,

        max_my_colors
    };

    enum Themes
    {
        cyan = 1,
        green,
        orange,
        dark,
        first_player_color,

        max_themes = 99
    };

    static void color_mvwaddch(WINDOW* win, int move_y, int move_x, int color_pair, const char symbol);
    static void color_mvwprintw(WINDOW* win, int move_y, int move_x, int color_pair, const char* format, ...);

    static void setThemeValue(const char* settingsFilePath);
    static void initColors();
    static void setTheme(WINDOW* win, short themeIndex);
    static std::vector<std::pair<int, int>> colorPairs;
    static short m_backgroundColor;
    static short m_currentColorPair;
};
#endif //GRAPHICSSETTINGS_HPP
