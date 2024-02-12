#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <stack>

#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Player.hpp"
#include "BaseMenu.hpp"
#include "Scores.hpp"

#include "Point.hpp"
#include "settings.hpp"
#include "graphics.hpp"

class Game
{
public:

    friend class StartMenu;

    Game();

    void startGame();

    ~Game()
    {
        wclear(m_winGame);
        wclear(m_winScore);

        wbkgd(m_winGame, graphics::ObjColors::black); //After the game is over, when we return to the menu,
        refreshWindow();                              //part of the playing field remains displayed,
        endwin();                                     //so we do this to make it invisible
    }

private:

    void spawnSnake();

    void spawnFood();

    void spawnOnBoard(const Point& point, char symbol);



    static std::array<Player, settings::playersAmount> setPlayers();

    void setNewDirections(std::vector<Snake::Direction>& directions);


    int getAnswer();

    void getInputs();

    std::string_view whoLose();

    static void handlePause(int ch) ;

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


    void makeGameBorder();


    static bool isPosAnotherSnake(const Player& testedSnake,
                           const Player& anotherSnake) ;


    std::vector<Score> getPlayersScores();

    static void saveScores(const std::vector<Score>& newScores, const char* scoresFilePath);


    static void stopGame() ;

    static void resumeGame() ;

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
