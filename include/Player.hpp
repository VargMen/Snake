#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <algorithm>

#include "Board.hpp"
#include "Snake.hpp"

class Player
{
public:
    Player() = default;

    Player(const Point& pos, const Snake::Direction& dir, std::string_view keys, std::string_view name)
    :m_snake{pos, dir}, m_keys{keys}, m_name{name}
    {
    }

    Player& operator=(const Player& player)
    {
        m_keys = player.m_keys;
        m_name = player.m_name;
        m_snake = player.m_snake;
    }

    void setKeys(const std::string& keys)
    {
        m_keys = keys;
    }


    std::string_view getKeys() const { return m_keys; }

    std::vector<Point> getSnakePos() const { return m_snake.getPos(); }

    Point getSnakeHead() const { return m_snake.getHead(); }

    const std::string& getName() const { return m_name; }

    int getSnakeScore() const { return m_snake.getScore(); }

    Snake& snake() { return m_snake; }

private:
    std::string m_keys{};
    std::string m_name{};

    Snake m_snake{};
};

#endif //PLAYER_H
