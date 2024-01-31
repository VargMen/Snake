#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <stack>

#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Player.hpp"

#include "Point.hpp"
#include "settings.hpp"

class Game
{
public:
    Game();

    void startGame();

    ~Game() { endwin(); }

private:

    Board m_board{settings::mapPath};

    std::vector<Player> m_players;

    std::vector<int> m_inputs{};

    int m_pauseTime {settings::firstPauseTime};

    Food m_food{Point{5, 5} };

    WINDOW * m_winGame{};
    WINDOW * m_winScore{};

    void setPlayersKeys();

    void setPlayers();

    int whoLose();

    bool handleOver(int whoLose);

    void spawnSnake();

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);

    void clearWindow();

    void refreshWindow();

    void printScore();

    void setNewDirections(std::vector<Snake::Direction>& directions);

    void getInputs();


    void restartGame();

    void printMessageToPlayAgain();

    int getAnswer();

    static bool isPosAnotherSnake(const Point& pos, const Snake& anotherSnake);

    void displayState();

    void updateState();

    void updatePauseTime();

    void handleInput(std::vector<Snake::Direction>& newDirs);
};


#endif //GAME_H
