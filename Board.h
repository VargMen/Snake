#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Vector2D.h"

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
    Board() = default;

    int getCellValue(Vector2D cell) const { return board[cell.x][cell.y]; }
    void setCellValue(Vector2D cell, MapSymbols symbol) { board[cell.x][cell.y] = symbol; }

    int board[10][10] = {
            {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, space, space, space, space, space, space, space, space, wall},
            {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall}
    };
};


#endif //BOARD_H
