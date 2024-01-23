#include "Snake.h"

Snake::Snake(int x, int y, int length, Direction dir)
        : m_length{length}, m_dir{dir}
{
    assert(x < setting::width && x > 0 && "Bad argument x in Snake()");
    assert(y < setting::height && y > 0 && "Bad argument y in Snake()");
    assert(length < setting::height - y && length > 0 && "Bad argument length in Snake()");

    m_snakePos.emplace_back(x, y);
    for(int i{1}; i < m_length; ++i)
        m_snakePos.emplace_back(x + i, y);

}

Vector2D Snake::newHeadPos()
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

void Snake::moveSnake()
{
    m_snakePos.pop_back();
    m_snakePos.insert(m_snakePos.begin(), newHeadPos()); //update the head and implicitly change the coordinates of the entire snake
}

bool Snake::isHitItself() const
{
    for(int i{1}; i < m_length; ++i)
        if(m_snakePos[0] == m_snakePos[i])
            return true;
    return false;
}

bool Snake::isOver() const
{
    return ((m_snakePos.begin()->x > setting::height - 2 || m_snakePos.begin()->x < 1) || (m_snakePos.begin()->y > setting::width-2 || m_snakePos.begin()->y < 1));
}

void Snake::levelUp()
{
    m_snakePos.insert(m_snakePos.begin(), newHeadPos());
    ++m_length;
    ++m_score;
}