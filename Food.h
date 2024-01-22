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
        m_pos.x = Random::get(1, 8);
        m_pos.y = Random::get(1, 8);
    }

    Vector2D getPos() const { return m_pos; }

    Vector2D m_pos {};
};


#endif //FOOD_H
