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

    int getCellValue(Vector2D cell) const { return m_board[cell.x][cell.y]; }
    void setCellValue(Vector2D cell, MapSymbols symbol) { m_board[cell.x][cell.y] = symbol; }
    void eraseBoard()
    {
        for(int i{1}; i < 9; ++i)      //цe touch everything except the walls
            for(int j{1}; j < 9; ++j)
                m_board[i][j] = space;
    }
    int m_board[10][10] = {
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
