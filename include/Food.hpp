#ifndef FOOD_H
#define FOOD_H

#include "../Util/Random.h"
#include "../Util/Vector2D.h"
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
        bool isPosFree{false};
        while(!isPosFree)
        {
            m_pos.x = Random::get(1, setting::height - 2);
            m_pos.y = Random::get(1, setting::width - 2);
        }
    }

    Vector2D getPos() const { return m_pos; }

    Vector2D m_pos {};
};


#endif //FOOD_H
