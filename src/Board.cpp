#include <fstream>

#include "../include/Board.hpp"

void Board::eraseBoard()
{
    for(int i{1}; i < setting::height - 1; ++i)
    {
        for(int j{1}; j < setting::width - 1; ++j)
        m_board[i][j] = m_clearBoard[i][j];
    }
}

bool Board::isPosWall(const Point& pos) const
{
    return m_clearBoard[pos.x][pos.y] == wall;
}

void Board::initByMap(std::string_view mapName) {
    std::ifstream file(mapName.data());
    if (!file.is_open())
    {
        assert(0 && "File is not found in function initByMap()");
    }

    for (int i {0}; i < setting::height; ++i)
    {
        std::string line;
        std::getline(file, line);

        for (int j {0}; j < setting::width; ++j)
        {
            char symbol = line[j];
            switch (symbol) {
                case '#':
                    m_board[i][j] = wall;
                    m_clearBoard[i][j] = wall;
                    break;
                case ' ':
                    m_board[i][j] = space;
                    m_clearBoard[i][j] = space;
                    break;
                default:;
                    assert(0 && "Invalid symbol of map in function initByMap()");
            }
        }
    }
}