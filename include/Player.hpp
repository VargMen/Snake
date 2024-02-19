#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <algorithm>

#include "Board.hpp"
#include "Snake.hpp"

class Player
{
public:
    enum PlayerSettings
    {
        NAME,
        MOVEMENT_KEYS,
        SNAKE_COLOR,
        SNAKE_SYMBOL
    };

    Player() = default;

    Player(const Point& pos, const Snake::Direction& dir, const std::vector<std::string>& playerSettings)
    :m_snake{pos, dir}, m_playerSettings{playerSettings}
    {
    }

    Player& operator=(const Player& player) = default;

    void setKeys(const std::string& keys)
    {
        m_playerSettings[MOVEMENT_KEYS] = keys;
    }


    std::string_view getKeys() const { return m_playerSettings[MOVEMENT_KEYS]; }

    std::vector<Point> getSnakePos() const { return m_snake.getPos(); }

    Point getSnakeHead() const { return m_snake.getHead(); }

    const std::string& getName() const { return m_playerSettings[NAME]; }

    int getSnakeScore() const { return m_snake.getScore(); }

    char getSnakeSymbol() const { return m_playerSettings[SNAKE_SYMBOL].front(); }

    int getSnakeColor() const { return stoi(m_playerSettings[SNAKE_COLOR]); }

    Snake& snake() { return m_snake; }

private:
    std::vector<std::string> m_playerSettings{};
    Snake m_snake{};
};

#endif //PLAYER_H
