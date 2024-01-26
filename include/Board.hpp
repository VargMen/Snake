#ifndef BOARD_H
#define BOARD_H

#include <string_view>

#include "Snake.hpp"
#include "Point.hpp"
#include "settings.hpp"

class Board
{
public:
    enum MapSymbols
    {
        wall = -1,
        space,
        snake,
        food,
        max_mapSymbols
    };

    explicit Board(std::string_view mapName) { initByMap(mapName); }

    void initByMap(std::string_view mapName);


    int getCellValue(const Point& cell) const { return m_board[cell.x][cell.y]; }

    void setCellValue(const Point& cell, const MapSymbols& symbol) { m_board[cell.x][cell.y] = symbol; }


    bool isPosWall(const Point& pos) const;


    void eraseBoard();

private:
    int m_board[setting::height][setting::width]{};
    int m_clearBoard[setting::height][setting::width]{};
};


#endif //BOARD_H