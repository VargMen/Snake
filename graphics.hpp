#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <ncurses.h>

namespace graphics
{
    enum MyColors
    {
        MyCOLOR_YELLOW = 8,
        MyCOLOR_GREEN,
        MyCOLOR_RED,
        MyCOLOR_GRAY,
        MyCOLOR_ORANGE,
        MyCOLOR_BLUE,

        max_my_colors
    };

    enum ObjColors
    {
        firstSnake = 1,
        secondSnake,
        thirdSnake,
        food,
        wall,
        space,

        bigWordSnakeInMenu,
        choicesInMenu,
        backgroundInMenu,

        backgroundInGame,

        black,
        max_colors
    };

    constexpr short backgroundColorInGame { MyCOLOR_YELLOW };
    constexpr short backgroundColorInMenu {  MyCOLOR_YELLOW };

    inline void initColor()
    {
        init_color(MyCOLOR_YELLOW, 247, 239, 183);
        init_color(MyCOLOR_GREEN, 21, 246, 21);
        init_color(MyCOLOR_GRAY, 180, 188, 180);
        init_color(MyCOLOR_ORANGE, 250, 175, 76);
        init_color(MyCOLOR_BLUE, 45, 146, 223);

        init_pair(ObjColors::bigWordSnakeInMenu, COLOR_GREEN, backgroundColorInMenu);

        init_pair(ObjColors::food, COLOR_RED, backgroundColorInGame);

        init_pair(ObjColors::firstSnake, COLOR_YELLOW, backgroundColorInGame);
        init_pair(ObjColors::secondSnake, COLOR_GREEN, backgroundColorInGame);
        init_pair(ObjColors::thirdSnake, COLOR_CYAN, backgroundColorInGame);

        init_pair(ObjColors::wall, COLOR_WHITE, backgroundColorInGame);
        init_pair(ObjColors::space, MyCOLOR_YELLOW, MyCOLOR_YELLOW);

        init_pair(ObjColors::black, COLOR_BLACK, COLOR_BLACK);
    }

    inline void setGameColor(WINDOW* gameWindow)
    {
        wbkgd(gameWindow, COLOR_PAIR(bigWordSnakeInMenu));
    }

    inline void setMenuColor(WINDOW* menuWin)
    {
        wbkgd(menuWin, COLOR_PAIR(bigWordSnakeInMenu));
    }

    inline void color_mvwprintw(WINDOW* win, int move_y, int move_x, int color_pair, const char* format, ...)
    {
        wattron(win, COLOR_PAIR(color_pair));

        va_list args;
        va_start(args, format);
        mvwprintw(win, move_y, move_x, format, args);
        va_end(args);

        wattroff(win, COLOR_PAIR(color_pair));
    }

    inline void color_mvwaddch(WINDOW* win, int move_y, int move_x, int color_pair, const char symbol)
    {
        wattron(win, COLOR_PAIR(color_pair));
        mvwaddch(win, move_y, move_x, symbol);
        wattroff(win, COLOR_PAIR(color_pair));
    }

    constexpr char wallSymbol { '#' };
    constexpr char spaceSymbol { ' ' };
    constexpr char foodSymbol { '*'};
    constexpr char* playerSymbols { "o0D"}; //i should make space at the beginning because of my implementation
                                          //and last space represent symbol for space
}
#endif //GRAPHICS_HPP
