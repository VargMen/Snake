#ifndef SNAKE_H
#define SNAKE_H

#include <cassert>
#include <vector>

#include "../Util/Vector2D.h"
#include "../settings.h"

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

    explicit Snake(int x, int y, int length, Direction dir);

    void updateDir(Direction dir) { m_dir = dir; }

    Vector2D newHeadPos();

    void moveSnake();

    bool isHitItself() const;

    bool isOver() const;

    bool isAte(Vector2D food_pos) const { return *m_snakePos.begin() == food_pos; }

    void levelUp();

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
