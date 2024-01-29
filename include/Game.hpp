#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <stack>

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

    Board m_board{setting::mapPath};

    std::vector<Snake> m_players{};

    std::stack<int> inputs{};

    int m_pauseTime {setting::firstPauseTime};

    Food m_food{Point{5, 5} };

    WINDOW * m_winGame{};
    WINDOW * m_winScore{};

    inline void stopGame() { wtimeout(m_winGame, -1); }

    inline void addSpeed() { timeout(m_pauseTime); }

    int whoLose();

    bool handleOver(int whoLose);

    void spawnSnake();

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);

    std::vector<Snake::Direction> parseStack();

    void clearWindow();

    void refreshWindow();

    void printScore();


    static Snake::Direction parseToDirection(int ch);

    void setNewDirections(std::vector<Snake::Direction>& directions);

    void getInputs();


    void restartGame();

    void printMessageToPlayAgain();

    int getAnswer();

    static bool isPosAnotherSnake(const Point& pos, const Snake& anotherSnake);

    void displayState();

    void updateState();

    void updatePauseTime();
};


#endif //GAME_H
