#ifndef BOARD_H
#define BOARD_H

#include "Snake.hpp"
#include "../Util/Point.hpp"
#include "../settings.h"

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

    int getCellValue(Point cell) const { return m_board[cell.x][cell.y]; }

    void setCellValue(Point cell, MapSymbols symbol) { m_board[cell.x][cell.y] = symbol; }

    void eraseBoard();

    void initBoard();

    int m_board[setting::height][setting::width]{};
};


#endif //BOARD_H