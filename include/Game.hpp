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

    void spawnSnake();

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);



    void setPlayers();

    void setNewDirections(std::vector<Snake::Direction>& directions);



    int getAnswer();

    void getInputs();

    std::string_view whoLose();

    void handlePause(int ch) const;

    std::vector<Snake::Direction> handleInput();



    void updateState();

    void updatePauseTime();



    void printScore();

    void printMessageToPlayAgain();

    void printLoser(const std::string& loser);

    void displayState();



    void clearWindow();

    void refreshWindow();



    void pause() const;

    void restartGame();



    bool isPosAnotherSnake(const Player& testedSnake,
                           const Player& anotherSnake) const ;



    void stopGame() const;

    void resumeGame() const;

private:

    WINDOW * m_winGame{};
    WINDOW * m_winScore{};
    std::array<Player, settings::playersAmount> m_players;
    Board m_board{settings::mapPath};
    Food m_food{Point{5, 5} };
    std::vector<int> m_inputs{};
    int m_pauseTime {settings::firstPauseTime};
};


#endif //GAME_H
