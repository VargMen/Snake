#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <algorithm>

#include "Snake.hpp"

class Player
{
public:
    Player(const Point& pos, const Snake::Direction& dir)
    : m_snake(pos, dir)
    {
    }

    void setKeys(const std::array<char, settings::keyNums>& keys)
    {
        m_keys = keys;
    }

    std::array<char, settings::keyNums> getKeys() { return m_keys; }

    Snake& snake() { return m_snake; }
private:
    std::array<char, settings::keyNums> m_keys;

    Snake m_snake;
};

#endif //PLAYER_H
