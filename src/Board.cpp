#include <fstream>

#include "../include/Board.hpp"

void Board::eraseBoard()
{
    for(int i{1}; i < settings::height - 1; ++i)
    {
        for(int j{1}; j < settings::width - 1; ++j)
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

    for (int i {0}; i < settings::height; ++i)
    {
        std::string line;
        std::getline(file, line);

        for (int j {0}; j < settings::width; ++j)
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