#include "Game.hpp"

Game::Game()
{
    initscr();
    noecho();
    int row, col;
    getmaxyx(stdscr, row, col);
    move(row/2, col/2);
    timeout(setting::speed * 100);
}

void Game::startGame()
{
    spawnSnake();
    spawnFood();

    while (!m_snake.isOver())
    {
        displayState();
        updateState();

        if(m_snake.isHitItself())
           break;
    }
}

void Game::spawnSnake()
{
    for(const auto& e: m_snake.getPos())
        m_board.setCellValue(e, Board::snake);
}

void Game::spawnFood()
{
    m_board.setCellValue(m_food.getPos(), Board::food);
}

Snake::Direction Game::getInput() {
    char input{};
    if ((input = getch()) != ERR) {
        switch (input) {
            case 'w':
                return Snake::Direction::up;
            case 's':
                return Snake::Direction::down;
            case 'a':
                return Snake::Direction::left;
            case 'd':
                return Snake::Direction::right;
            default:
                return Snake::Direction::max_directions;
        }
    }
}

void Game::displayState()
{
    for (int i {0}; i < setting::height; ++i) {
        for (int j {0}; j < setting::width; ++j) {
            switch( m_board.getCellValue(Point{i, j}) )
            {
                case Board::MapSymbols::space:
                    mvaddch(i, j, ' ');
                    break;
                case Board::MapSymbols::wall:
                    mvaddch(i, j, '#');
                    break;
                case Board::MapSymbols::snake:
                    mvaddch(i, j, 'o');
                    break;
                case Board::MapSymbols::food:
                    mvaddch(i, j, '*');
                    break;
                default:
                    assert(0 && "Unknown symbol in board\n");
            }
        }
    }
    refresh();
}

void Game::updateState()
{
    m_board.eraseBoard();

    spawnFood();

    Snake::Direction newDir { getInput() };
    if(newDir != Snake::Direction::max_directions) //If we don't press a key to change the direction
        m_snake.updateDir(newDir);

    if(m_snake.isAte(m_food.getPos()))
    {
        m_snake.levelUp();
        while(true)
        {
            m_food.makeRandomPos();
            auto it {std::find(m_snake.getPos().begin(),           //We check that the food has not spawned
                               m_snake.getPos().end(), m_food.getPos())};//in the place where there is currently a snake
            if(it == m_snake.getPos().end())
                break;

        }
    }
    else
        m_snake.moveSnake();

    spawnSnake();

}
