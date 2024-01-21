#ifndef GAME_H
#define GAME_H

#include <iostream>

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
        spawnSnake();
        spawnFood();

        while(!m_snake.isOver())
        {
            displayState();
            updateState();
        }
        std::cout << "You lose!\n";
    }

private:
    Board m_board{};
    Snake m_snake{3, 3, 3, Snake::Direction::up};
    Food m_food{5, 5};


    void spawnSnake()
    {
        m_board.setCellValue(m_snake.getPos(), Board::snake);
    }

    void spawnFood()
    {
        m_board.setCellValue(m_food.getPos(), Board::food);
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
                    return Snake::Direction::left;
                case 's':
                    return Snake::Direction::right;
                case 'a':
                    return Snake::Direction::up;
                case 'd':
                    return Snake::Direction::down;
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
                switch( m_board.getCellValue(Vector2D{i, j}) )
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
        m_board.setCellValue(m_snake.getPos(), Board::space);

        Snake::Direction newDir { getInput() };
        m_snake.updateDir(newDir);

        m_snake.moveSnake();
        m_board.setCellValue(m_snake.getPos(), Board::snake);
    }

};


#endif //GAME_H
