#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>

#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#include "../Util/Point.hpp"
#include "../settings.h"

class Game
{
public:
    Game();

    void startGame();

    ~Game() { endwin(); }

private:
    Board m_board{};
    Snake m_snake{3, 3, 1, Snake::Direction::up};
    Food m_food{5, 5};
    WINDOW * m_win{};


    void spawnSnake();

    void spawnFood();

    Snake::Direction getInput();

    void displayState();

    void updateState();

};


#endif //GAME_H
