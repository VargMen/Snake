#include <fstream>

#include "Board.hpp"


Board::Board(const std::string& mapName, int width, int height)
                :m_width(width), m_height(height)
{
    assert(m_height > 0 && m_width > 0 && "Bad width and height for Board()");

    m_board.resize(m_height);
    m_clearBoard.resize(m_height);

    for(std::size_t i{0}; i < m_height; ++i)
    {
        m_board[i].resize(m_width);
        m_clearBoard[i].resize(m_width);
    }

    initByMap(mapName);
}

void Board::eraseBoard()
{
    for(int i{1}; i < m_height - 1; ++i)
    {
        for(int j{1}; j < m_width - 1; ++j)
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

    for (int i {0}; i < m_height; ++i)
    {
        std::string line;
        std::getline(file, line);

        for (int j {0}; j < m_width; ++j)
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
