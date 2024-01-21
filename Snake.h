#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>

class Snake
{
public:
    enum Direction
    {
        up,
        down,
        left,
        right,
        max_directions
    };

    explicit Snake(int x = 3, int y = 2, int length = 1, Direction dir = up)
    : m_posX{x}, m_posY{y}, m_length{length}, m_dir{dir}
    {
    }

    void updateDir(Direction dir)
    {
        m_dir = dir;
    }

    void moveSnake()
    {
        switch(m_dir)
        {
            case up:
                --m_posY;
                break;
            case down:
                ++m_posY;
                break;
            case left:
                --m_posX;
                break;
            case right:
                ++m_posX;
                break;
            default:
                assert(0 && "Bad direction in updateDir()");

        }
    }

    bool isOver()
    {
        return ((m_posX > 9 || m_posX < 1) || (m_posY > 9 || m_posY < 1));
    }

    int getX() { return m_posX; }
    int getY() { return m_posY; }

    int m_posX{};
    int m_posY{};
    int m_length{};
    Direction m_dir{};

};


#endif //SNAKE_H
