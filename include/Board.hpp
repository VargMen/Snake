#ifndef BOARD_H
#define BOARD_H

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
    Board() { initBoard(); }

    int getCellValue(const Point& cell) const { return m_board[cell.x][cell.y]; }

    void setCellValue(const Point& cell, const MapSymbols& symbol) { m_board[cell.x][cell.y] = symbol; }

    void eraseBoard();

    void initBoard();

    int m_board[setting::height][setting::width]{};
};


#endif //BOARD_H