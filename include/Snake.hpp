#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>
#include <vector>

#include "Point.hpp"
#include "settings.h"

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

    explicit Snake(const Point& pos, Direction dir);

    void updateDir(Direction dir) { m_dir = dir; }

    Point newHeadPos();

    void moveSnake();

    bool isHitItself();

    bool isOver() const;

    bool isAte(Point food_pos) const { return *m_snakePos.begin() == food_pos; }

    void levelUp();

    int getLength() const { return m_length; }
    int getScore() const { return m_score; }
    std::vector<Point> getPos() const { return m_snakePos; }
    bool getFlagHitItself() const { return isHitItselfFlag; }
private:
    std::vector<Point> m_snakePos{};
    int m_length{};
    Direction m_dir{};
    int m_score{};
    bool isHitItselfFlag{false};
};


#endif //SNAKE_H
