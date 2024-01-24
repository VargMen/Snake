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
    bool isGamePause{false};
    void spawnSnake();

    void spawnFood();

    void pauseGame();
    Snake::Direction getInput();

    void displayState();

    void updateState();

    void restartGame();
};


#endif //GAME_H
