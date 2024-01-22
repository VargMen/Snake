#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>
#include <vector>
#include <algorithm> //for std::swap
#include "Vector2D.h"

class Snake
{
public:
    enum class Direction
    {
        up,
        down,
        left,
        right,
        max_directions
    };

    explicit Snake(int x, int y, int length, Direction dir)
    : m_length{length}, m_dir{dir}
    {
        m_snakePos.emplace_back(x, y);
        for(int i{1}; i < m_length; ++i)
            m_snakePos.emplace_back(x + i, y);

    }

    void updateDir(Direction dir)
    {
        m_dir = dir;
    }

    Vector2D newHeadPos()
    {
        Vector2D result { *m_snakePos.begin() };
        if(m_dir == Direction::up)
        {
            --result.y;
        }
        if(m_dir == Direction::down)
        {
            ++result.y;
        }
        if(m_dir == Direction::left)
        {
            --result.x;
        }
        if(m_dir == Direction::right)
        {
            ++result.x;
        }
        return result;
    }

    void moveSnake()
    {
        m_snakePos.pop_back();
        m_snakePos.insert(m_snakePos.begin(), newHeadPos()); //update the head and implicitly change the coordinates of the entire snake
    }
    bool isOver() const
    {
        return ((m_snakePos.begin()->x > 8 || m_snakePos.begin()->x < 1) || (m_snakePos.begin()->y > 8 || m_snakePos.begin()->y < 1));
    }
    bool isAte(Vector2D food_pos) const
    {
        return *m_snakePos.begin() == food_pos;
    }
    void levelUp()
    {
        m_snakePos.insert(m_snakePos.begin(), newHeadPos());
        ++m_length;
        ++m_score;
    }

    int getLength() const { return m_length; }
    int getScore() const { return m_score; }
    std::vector<Vector2D> getPos() const { return m_snakePos; }

private:
    std::vector<Vector2D> m_snakePos{};
    int m_length{};
    Direction m_dir{};
    int m_score{};
};


#endif //SNAKE_H
