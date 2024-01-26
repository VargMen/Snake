#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>

#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#include "Point.hpp"
#include "settings.hpp"

class Game
{
public:
    Game();

    void startGame();

    ~Game() { endwin(); }

private:
    Board m_board{};
    Snake m_snake{Point{3, 3}, Snake::Direction::up};
    Food m_food{Point{5, 5} };
    WINDOW * m_winGame{};
    WINDOW * m_winScore{};
    bool loseFlag{false};

    void spawnSnake();

    void clearWindow();

    void refreshWindow();

    void printScore();

    void printMessageToPlayAgain();

    static Snake::Direction parseToDirection(int ch);

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);

    Snake::Direction getNewDirection();

    int getAnswer();

    void displayState();

    void updateState();

    void addSpeed();

    void stopGame();

    void restartGame();
};


#endif //GAME_H
