#include "Snake.hpp"

Snake::Snake(const Point& pos, const Direction& dir)
        : m_length{1}, m_dir{dir}
{
    assert(pos.x < setting::width && pos.x > 0 && "Bad argument x in Snake()");
    assert(pos.y < setting::height && pos.y > 0 && "Bad argument y in Snake()");

    m_snakePos.emplace_back(pos);
}

Point Snake::newHeadPos()
{
    Point result { m_snakePos.front() };
    switch(m_dir)
    {
        case Direction::up:
            --result.x;
            break;
        case Direction::down:
            ++result.x;
            break;
        case Direction::left:
            --result.y;
            break;
        case Direction::right:
            ++result.y;
    }
    return result;
}

void Snake::moveSnake()
{
    m_snakePos.pop_back();
    m_snakePos.insert(m_snakePos.begin(), newHeadPos()); //update the head and implicitly change the coordinates of the entire snake
}

bool Snake::isHitItself()
{
    for(int i{1}; i < m_length; ++i)
        if(m_snakePos[0] == m_snakePos[i])
        {
            return true;
        }
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

Snake::Direction operator-(const Snake::Direction& dir)
{
    switch(dir)
    {
        case Snake::Direction::up:
            return Snake::Direction::down;
        case Snake::Direction::down:
            return Snake::Direction::up;
        case Snake::Direction::left:
            return Snake::Direction::right;
        case Snake::Direction::right:
            return Snake::Direction::left;
        case Snake::Direction::max_directions:
            assert(0 && "Bad direction in operator-");
    }
}