#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>

#include "Board.h"
#include "Snake.h"
#include "Food.h"

#include "Vector2D.h"

class Game
{
public:
    Game() = default;

    void startGame()
    {
        initscr();
        noecho();

        timeout(300);

        spawnSnake();
        spawnFood();

        while (!m_snake.isOver()) {
            displayState();
            updateState();
            if(m_snake.isHitItself())
                break;
        }
        std::cout << "You lose!\n";

    }

    ~Game() { endwin(); }

private:
    Board m_board{};
    Snake m_snake{3, 3, 1, Snake::Direction::up};
    Food m_food{5, 5};


    void spawnSnake()
    {
        for(const auto& e: m_snake.getPos())
            m_board.setCellValue(e, Board::snake);
    }

    void spawnFood()
    {
        m_board.setCellValue(m_food.getPos(), Board::food);
    }

    Snake::Direction getInput() {
        char input{};
        if ((input = getch()) != ERR) {
            switch (input) {
                case 'w':
                    return Snake::Direction::left;
                case 's':
                    return Snake::Direction::right;
                case 'a':
                    return Snake::Direction::up;
                case 'd':
                    return Snake::Direction::down;
            }
        }
        return Snake::Direction::max_directions;
    }

    void displayState() {

        move(10, 10);
        box(stdscr, 0, 0);

        std::cout << "            Score: " << m_snake.getScore() << '\n';
        for (int i {0}; i < 10; ++i) {
            for (int j {0}; j < 10; ++j) {
                switch( m_board.getCellValue(Vector2D{i, j}) )
                {
                    case 0:
                        mvprintw(i, j, " ");
                        break;
                    case -1:
                        mvprintw(i, j, "#");
                        break;
                    case 1:
                        mvprintw(i, j, "o");
                        break;
                    case 2:
                        mvprintw(i, j, "*");
                        break;
                    default:
                        std::cout << "Unknown symbol in board\n";
                        exit(-1);
                }
            }
            std::cout << '\n';
        }
    }


    void updateState()
    {
        m_board.eraseBoard();

        spawnFood();

        Snake::Direction newDir { getInput() };
        if(newDir != Snake::Direction::max_directions)
            m_snake.updateDir(newDir);

        if(m_snake.isAte(m_food.getPos()))
        {
            m_snake.levelUp();
            m_food.makeRandomPos();
        }
        else
            m_snake.moveSnake();

        for(const auto& e: m_snake.getPos())
            m_board.setCellValue(e, Board::snake);

    }

};


#endif //GAME_H
