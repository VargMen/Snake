#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>

#include "Vector2D.h"

class Snake
{
public:
    enum class Direction : int
    {
        up,
        down,
        left,
        right,
        max_directions
    };

    explicit Snake(int x, int y, int length, Direction dir)
    : m_pos{x, y}, m_length{length}, m_dir{dir}
    {
    }

    void updateDir(Direction dir)
    {
        m_dir = dir;
    }

    void moveSnake()
    {
        if(m_dir == Direction::up)
        {
            --m_pos.y;
        }
        if(m_dir == Direction::down)
        {
            ++m_pos.y;
        }
        if(m_dir == Direction::left)
        {
            --m_pos.x;
        }
        if(m_dir == Direction::right)
        {
            ++m_pos.x;
        }
    }

    bool isOver() const
    {
        return ((m_pos.x > 8 || m_pos.x < 1) || (m_pos.y > 8 || m_pos.y < 1));
    }

    Vector2D getPos() const { return m_pos; }

private:
    Vector2D m_pos{3, 3};
    int m_length{3};
    Direction m_dir{Direction::up};

};


#endif //SNAKE_H
