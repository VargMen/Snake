#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>
#include <vector>

#include "Point.hpp"
#include "settings.hpp"

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

    explicit Snake(const Point& pos, const Direction& dir);

    friend Direction operator-(const Direction& dir);

    void updateDir(const Direction& dir);


    Point newHeadPos();

    void moveSnake();


    void levelUp();


    bool isHitItself();

    bool isAte(const Point& food_pos) const { return m_snakePos.front() == food_pos; }


    int getScore() const { return m_score; }

    std::vector<Point> getPos() const { return m_snakePos; }

    Direction getDir() const { return m_dir; }

    int getPauseTime() const { return m_pauseTime; }

private:
    std::vector<Point> m_snakePos{};
    int m_length{};
    Direction m_dir{};
    int m_score{};
    int m_pauseTime{setting::firstPauseTime};
};


#endif //SNAKE_H
