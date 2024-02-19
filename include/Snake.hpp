#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Point.hpp"
#include "settings.hpp"

class Snake
{
public:
    friend class Player;

    enum class Direction
    {
        up,
        down,
        left,
        right,
        max_directions

    };

    Snake() = default;

    explicit Snake(const Point& pos, const Direction& dir);

    Snake& operator=(const Snake& snake) = default;



    friend Direction operator-(const Direction& dir);

    void updateDir(const Direction& dir);



    Point newHeadPos();

    void moveSnake();



    void levelUp();

    bool isAte(const Point& food_pos) const { return m_snakePos.front() == food_pos; }

    bool isHitItself() const;



    int getScore() const { return m_score; }

    std::vector<Point> getPos() const { return m_snakePos; }

    Direction getDir() const { return m_dir; }

    Point getHead() const { return m_snakePos[0]; }


private:
    std::vector<Point> m_snakePos{};
    int m_length{};
    Direction m_dir{};
    int m_score{};
};


#endif //SNAKE_H
