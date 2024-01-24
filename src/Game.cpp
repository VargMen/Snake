#include "Game.hpp"

Game::Game()
{
    initscr();
    noecho();
    int row, col;
    getmaxyx(stdscr, row, col);

    m_winGame = newwin(setting::height+1, setting::width+1, 0, 0);
    m_winScore = newwin(setting::height+1, 20, 1, setting::width+2); //20 is size for window with score and etc

    curs_set(0);
    nodelay(m_winGame, TRUE);

    wtimeout(m_winGame, setting::speed * 100);
}

void Game::startGame()
{
    int answer{};

    do
    {
        spawnSnake();
        spawnFood();

        while (!m_snake.isOver()) {
            displayState();
            updateState();

            if (!isGamePause)                //I do this because when i pause game the snake's coordinate remain
            {                                //unchanged and when it trie to check whether snake hit itself
                if (m_snake.isHitItself())   //after pause it will be true
                {
                    break;
                }
            }
            isGamePause = false;
        }

        displayState();

        restartGame();              //we restart game anyway
        answer = wgetch(m_winGame);
        wtimeout(m_winGame, setting::speed * 100);
    } while(answer == 'y');     //but proceed play if we want to do it
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

    int input{};

    if ((input = wgetch(m_winGame)) != ERR) {
        switch (input) {
            case 'w':
                return Snake::Direction::up;
            case 's':
                return Snake::Direction::down;
            case 'a':
                return Snake::Direction::left;
            case 'd':
                return Snake::Direction::right;
            case 'p':
                isGamePause = true;
            default : ;
        }
    }
    return Snake::Direction::max_directions;
}

void Game::displayState()
{
    wclear(m_winGame);
    wclear(m_winScore); //I do this because "You lose!" is still printed after we restart

    for (int i {0}; i < setting::height; ++i) {
        for (int j {0}; j < setting::width; ++j) {
            switch( m_board.getCellValue(Point{i, j}) )
            {
                case Board::MapSymbols::space:
                    mvwaddch(m_winGame, i, j, ' ');
                    break;
                case Board::MapSymbols::wall:
                    mvwaddch(m_winGame, i, j, '#');
                    break;
                case Board::MapSymbols::snake:
                    mvwaddch(m_winGame, i, j, 'o');
                    break;
                case Board::MapSymbols::food:
                    mvwaddch(m_winGame, i, j, '*');
                    break;
                default:
                    assert(0 && "Unknown symbol in board\n");
            }
        }
    }

    wmove(m_winScore, 0 , 0);
    wprintw(m_winScore, "Score: %d", m_snake.getScore());
    if(m_snake.isOver() || m_snake.getFlagHitItself())
    {
        wtimeout(m_winGame, -1);
        wtimeout(m_winScore, -1);
        wmove(m_winScore, 3 , 0);
        wprintw(m_winScore, "You lose!");
        wmove(m_winScore, 5 , 0);
        wprintw(m_winScore, "Write 'y' and try again >:D");
    }
    wrefresh(m_winScore);
    wrefresh(m_winGame);
}

void Game::updateState()
{
    m_board.eraseBoard();

    spawnFood();

    Snake::Direction newDir { getInput() };

    if(!isGamePause)
    {
        if (newDir != Snake::Direction::max_directions) //If we don't press a key to change the direction
            m_snake.updateDir(newDir);
    }
    else
        pauseGame();

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

void Game::pauseGame()
{
    wtimeout(m_winGame, -1);
    Snake::Direction newDir { getInput() };
    m_snake.updateDir(newDir);
    wtimeout(m_winGame, setting::speed * 100);
}

void Game::restartGame()
{
    m_board = Board{};
    m_snake = Snake{Point{3, 3}, Snake::Direction::up};
    m_food = Food{5, 5};
}