#ifndef FOOD_H
#define FOOD_H

#include "Random.h"

class Food
{
public:
    Food(int x = 5, int y = 5)
        :m_posX(x), m_posY(y)
    {
    }

    void makeRandomPos()
    {
        m_posX = Random::get(1, 9);
        m_posY = Random::get(1, 9);
    }

    int getX() { return m_posX; }
    int getY() { return m_posY; }

    int m_posX {};
    int m_posY {};
};


#endif //FOOD_H
