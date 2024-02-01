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

    friend class Menu;

    Game();

    void startGame();

    ~Game() { endwin(); }

private:
    bool isOver() const;

    void spawnSnake();
<<<<<<< HEAD

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);



    std::array<Player, settings::playersAmount> setPlayers();

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
=======
    void spawnFood();
    void spawnOnBoard(const Point& point, char symbol);


    void clearWindow();
    void refreshWindow();

    void printScore();
    void printMessageToPlayAgain();


    static Snake::Direction parseToDirection(int ch);
    Snake::Direction getNewDirection();

    int getAnswer();

    void displayState();
    void updateState();

    void addSpeed();

    void stopGame();
    void restartGame();

private:
    Board m_board{setting::mapPath};
    Snake m_snake{Point{3, 3}, Snake::Direction::up};
    Food m_food{Point{5, 5} };
    WINDOW * m_winGame{};
    WINDOW * m_winScore{};
    bool loseFlag{false};
>>>>>>> aa5c93e9a28fb4eb090482b4d45f5d76d03c4cd5
};


#endif //GAME_H
