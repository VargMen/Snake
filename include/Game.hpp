#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>

#include "Board.hpp"
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>

#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#include "Point.hpp"
#include "settings.h"

class Game
{
public:
    Game();

    void startGame();

    ~Game() { endwin(); }

private:
    Board m_board{};
    Snake m_snake{Point{3, 3}, Snake::Direction::up};
    Food m_food{5, 5};
    WINDOW * m_winGame{};
    WINDOW * m_winScore{};
    bool loseFlag{false};

    void spawnSnake();

    Snake::Direction parseToDirection(int ch);

    void spawnFood();

    Snake::Direction getInput();

    void displayState();

    void displayLoseState();

    void updateState();

    void addSpeed();

    void stopGame();

    void restartGame();
};


#endif //GAME_H

