#ifndef FOOD_H
#define FOOD_H

#include "Random.hpp"
#include "Point.hpp"
#include "settings.hpp"

class Food
{
public:
    explicit Food(const Point& pos)
        : m_pos{ pos }
    {
        assert(pos.x < settings::height && pos.x > 0 && "Bad argument x in Food()");
        assert(pos.y < settings::width && pos.y > 0 && "Bad argument y in Food()");
    }


    void makeRandomPos()
    {
            m_pos.x = Random::get(1, settings::height - 2);
            m_pos.y= Random::get(1, settings::width - 2);
    }

    Point getPos() const { return m_pos; }

private:

    Point m_pos {};
};


#endif //FOOD_H
