#include "GraphicsSettings.hpp"
#include <fstream>


std::vector<std::pair<int, int>> GraphicsSettings::colorPairs{{MyCOLOR_BLUE, COLOR_CYAN},
                                                              {COLOR_WHITE, COLOR_BLACK},
                                                              {COLOR_GREEN, MyCOLOR_GREEN},
                                                              { COLOR_RED, MyCOLOR_ORANGE}};
short GraphicsSettings::m_backgroundColor = 0;

short GraphicsSettings::m_currentColorPair = 0;

void GraphicsSettings::initColors()
{
    init_color(MyCOLOR_YELLOW, 247, 239, 183);
    init_color(MyCOLOR_GREEN, 21, 246, 21);
    init_color(MyCOLOR_GRAY, 180, 188, 180);
    init_color(MyCOLOR_ORANGE, 250, 175, 76);
    init_color(MyCOLOR_BLUE, 45, 146, 223);

    short i {1};
    for(const auto& pair: colorPairs)
    {
        init_pair(i, static_cast<short>(pair.first), static_cast<short>(pair.second));
        ++i;
    }
}

void GraphicsSettings::setTheme(WINDOW* win, short themeIndex)
{
    wbkgd(win, COLOR_PAIR(themeIndex));
    m_backgroundColor = static_cast<short>(colorPairs[themeIndex - 1].second);
    m_currentColorPair = themeIndex;
}

void GraphicsSettings::color_mvwprintw(WINDOW* win, int move_y, int move_x, int color_pair, const char* format, ...)
{
    wattron(win, COLOR_PAIR(color_pair));

    va_list args;
    va_start(args, format);
    mvwprintw(win, move_y, move_x, format, args);
    va_end(args);

    wattroff(win, COLOR_PAIR(color_pair));
}

void GraphicsSettings::color_mvwaddch(WINDOW* win, int move_y, int move_x, int color_pair, const char symbol)
{
    wattron(win, COLOR_PAIR(color_pair));
    mvwaddch(win, move_y, move_x, symbol);
    wattroff(win, COLOR_PAIR(color_pair));
}

void GraphicsSettings::setThemeValue(const char* settingsFilePath)
{
    std::fstream settingsFile { settingsFilePath };

    if (!settingsFile.is_open())
        assert(0 && "failed to open playerSettingFile in parsePlayerSettings()");

    std::string line;

    while (std::getline(settingsFile, line))
    {
        size_t colonIndex { line.find("Theme: ") };
        if(colonIndex != std::string::npos)
        {
            m_currentColorPair = static_cast<short>(stoi(line.substr(colonIndex + 7)));
            m_backgroundColor = static_cast<short>(colorPairs[m_currentColorPair].second);
        }
    }
}
