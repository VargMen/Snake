#include "../include/Board.hpp"

void Board::eraseBoard()
{
    for(int i{1}; i < setting::height - 1; ++i)      //this touch everything
        for(int j{1}; j < setting::width - 1; ++j)  //except the walls
            m_board[i][j] = space;
}

void Board::initBoard()
{
    // Fill the borders with wall
    for (int i = 0; i < setting::height; ++i) {
        for (int j = 0; j < setting::width; ++j) {
            if (i == 0 || i == setting::height - 1 || j == 0 || j == setting::width - 1) {
                m_board[i][j] = wall;
            }
        }
    }
}