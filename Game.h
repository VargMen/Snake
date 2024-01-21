#ifndef SNAKE_1_GAME_H
#define SNAKE_1_GAME_H

#include <iostream>

#include "Board.h"
#include "Snake.h"
#include "Food.h"

class Game
{
public:
    Game() { startGame(); }

    Board m_board{};
    Snake m_snake{};
    Food m_food{};

    void startGame()
    {
        spawnSnake();
        spawnFood();

        while(!m_snake.isOver())
        {
            displayState();
            updateState();
        }
        std::cout << "You lose!\n";
    }

    void spawnSnake()
    {
        m_board(m_snake.getX(), m_snake.getY()) = 1;
    }

    void spawnFood()
    {
        m_board(m_food.getX(), m_food.getY()) = 2;
    }

    Snake::Direction getInput()
    {
        while (true) // Loop until user enters a valid input
        {
            char input{};
            std::cin >> input;

            if (!std::cin) // if the previous extraction failed
            {
                if (std::cin.eof()) // if the stream was closed
                {
                    exit(0); // shut down the program now
                }

                // let's handle the failure
                std::cin.clear(); // put us back in 'normal' operation mode
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Check whether the user entered meaningful input
            switch (input)
            {
                case 'w':
                    return Snake::left;
                case 's':
                    return Snake::right;
                case 'a':
                    return Snake::up;
                case 'd':
                    return Snake::down;
                default:
                    std::cout << "Oops, that input is invalid.  Please try again.\n";
            }
        } // and try again
    }

    void displayState() {
        for (int i{0}; i < 20; ++i)
            std::cout << '\n';

        for (int i {0}; i < 10; ++i) {
            for (int j {0}; j < 10; ++j) {
                switch( m_board(i, j) )
                {
                    case 0:
                        std::cout << ' ';
                        break;
                    case -1:
                        std::cout << '#';
                        break;
                    case 1:
                        std::cout << 'o';
                        break;
                    case 2:
                        std::cout << '*';
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
        m_board(m_snake.getX(), m_snake.getY()) = 0;

        m_snake.updateDir(getInput());

        m_snake.moveSnake();

        m_board(m_snake.getX(), m_snake.getY()) = 1;
    }

};


#endif //GAME_H
