#ifndef FOOD_H
#define FOOD_H

#include "../Util/Random.hpp"
#include "../Util/Point.hpp"
#include "../settings.h"

class Food
{
public:
    explicit Food(int x, int y)
        : m_pos{x, y}
    {
        assert(x < setting::height && x > 0 && "Bad argument x in Food()");
        assert(y < setting::width && y > 0 && "Bad argument y in Food()");
    }

    void makeRandomPos()
    {
            m_pos.x = Random::get(1, setting::height - 2);
            m_pos.y = Random::get(1, setting::width - 2);
    }

    Point getPos() const { return m_pos; }

    Point m_pos {};
};


#endif //FOOD_H
