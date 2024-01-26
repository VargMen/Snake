#include "Game.hpp"

Game::Game()
{
    initscr();
    noecho();

    m_winGame = newwin(setting::height+1, setting::width+1, 0, 0);
    m_winScore = newwin(setting::height+1, 30, 1, setting::width+2); //20 is size for window with score and etc

    curs_set(0);
    nodelay(m_winGame, TRUE);

    addSpeed();
}

void Game::startGame()
{
    int answer{};

    do
    {
        spawnSnake();
        spawnFood();

        while (!loseFlag && !m_snake.isOver()) {
            displayState();
            updateState();

            if (m_snake.isHitItself())
            {
                loseFlag = true;
            }
        }

        //We come here when we have lost

        stopGame(); //we stop the game because we want to know if the player wants to play anymore

        printMessageToPlayAgain();

        restartGame();              //we restart game anyway
        answer = getAnswer();

        addSpeed();

    } while(answer == 'y');     //but proceed play if we want to do it
}

int Game::getAnswer()
{
    int answer{};

    do {
        answer = wgetch(m_winGame);
    } while (answer != 'y' && answer != 'n');

    return answer;
}

void Game::spawnSnake()
{
    for(const auto& e: m_snake.getPos())
    {
        m_board.setCellValue(e, Board::snake);
    }
}

void Game::spawnFood()
{
    m_board.setCellValue(m_food.getPos(), Board::food);
}

Snake::Direction Game::getNewDirection() {

    int input{};

    if ((input = wgetch(m_winGame)) != ERR) {
        if(input == 'p')
        {
            do
            {
                stopGame();

                input = wgetch(m_winGame);
            } while(input == 'p');  //here we handle case when a player trying to press 'p' more than once consecutively

            addSpeed();

            return parseToDirection(input);

        } else {
            return parseToDirection(input);
        }
    }
    return Snake::Direction::max_directions;
}

void Game::clearWindow()
{
    wclear(m_winGame);
    wclear(m_winScore);
}

void Game::refreshWindow()
{
    wrefresh(m_winScore);
    wrefresh(m_winGame);
}

void Game::printScore()
{
    wmove(m_winScore, 0 , 0);
    wprintw(m_winScore, "Score: %d", m_snake.getScore());

}

void Game::displayState()
{
    clearWindow(); //I do this because "You lose!" is still printed after we restart

    for (int i {0}; i < setting::height; ++i)
    {
        for (int j {0}; j < setting::width; ++j)
        {
            spawnOnBoard(Point{i, j}, static_cast<char>(m_board.getCellValue( Point{i, j} )));
        }
    }

    printScore();

    refreshWindow();
}

void Game::updateState()
{
    addSpeed(); //if the pause time changes, we set these changes here
    m_board.eraseBoard();

    spawnFood();

    Snake::Direction newDir { getNewDirection() };

    if(newDir == -m_snake.getDir())    //we do not allow players to rotate the snake 180 degrees
    {
        newDir = Snake::Direction::max_directions; //and in this case we just return previous direction
    }

    if (newDir != Snake::Direction::max_directions) //If we don't press a key to change the direction
    {
        m_snake.updateDir(newDir);
    }

    if(m_snake.isAte(m_food.getPos())) //if snake ate the food, we make new food
    {
        m_snake.levelUp();
                                //we don't call moveSnake() here because we want to increase length of snake
        m_food.makeRandomPos(); //it means we don't delete last element of snake but just add new head

    } else {
        m_snake.moveSnake(); //if we don't ate food, we just move snake
    }

    spawnSnake();
}

void Game::restartGame()
{
    m_board = Board{};
    m_snake = Snake{Point{3, 3}, Snake::Direction::up};
    m_food = Food{Point{5, 5}};
    loseFlag = false;
}

void Game::spawnOnBoard(const Point& point, char symbol)
{
    switch( symbol )
    {
        case Board::MapSymbols::space:
            mvwaddch(m_winGame, point.x, point.y, ' ');
            break;
        case Board::MapSymbols::wall:
            mvwaddch(m_winGame, point.x, point.y, '#');
            break;
        case Board::MapSymbols::snake:
            mvwaddch(m_winGame, point.x, point.y, 'o');
            break;
        case Board::MapSymbols::food:
            mvwaddch(m_winGame, point.x, point.y, '*');
            break;
        default:
            assert(0 && "Unknown symbol in board\n");
    }
}

void Game::printMessageToPlayAgain()
{
    wmove(m_winScore, 3 , 0);
    wprintw(m_winScore, "You lose!");
    wmove(m_winScore, 5 , 0);
    wprintw(m_winScore, "Write 'y' and try again >:D");
    wmove(m_winScore, 7 , 0);
    wprintw(m_winScore, "or 'n' otherwise :(");
    wrefresh(m_winScore);
}
Snake::Direction Game::parseToDirection(int ch)
{
    switch(ch)
    {
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


inline void Game::addSpeed() { wtimeout(m_winGame, m_snake.getPauseTime()); }

inline void Game::stopGame() { wtimeout(m_winGame, -1); }