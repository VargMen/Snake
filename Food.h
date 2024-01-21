#ifndef FOOD_H
#define FOOD_H

#include "Random.h"
#include "Vector2D.h"

class Food
{
public:
    explicit Food(int x, int y)
        : m_pos{x, y}
    {
    }

    void makeRandomPos()
    {
        m_pos.x = Random::get(1, 9);
        m_pos.y = Random::get(1, 9);
    }

    Vector2D getPos() const { return m_pos; }

    Vector2D m_pos {5, 5};
};


#endif //FOOD_H
