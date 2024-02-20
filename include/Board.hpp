#ifndef BOARD_H
#define BOARD_H

#include "Snake.hpp"
#include "Point.hpp"

class Board
{
public:
    enum MapSymbols
    {
        wall = -3,
        space,
        food,

        max_mapSymbols = 99
    };
    Board(const std::string& mapName, int width, int height);

    Board() = default;

    void initByMap(std::string_view mapName);



    int getCellValue(const Point& cell) const { return m_board[cell.x][cell.y]; }

    void setCellValue(const Point& cell, int symbol) { m_board[cell.x][cell.y] = symbol; }



    bool isPosWall(const Point& pos) const;

    void eraseBoard();

private:
    int m_height{};
    int m_width{};

    std::vector<std::vector<int>> m_board{};
    std::vector<std::vector<int>> m_clearBoard{};
};

#endif //BOARD_H