#include "Game.hpp"

Game::Game()
{
    initscr();
    noecho();

    m_winGame = newwin(setting::height+1, setting::width+1, 0, 0);
    m_winScore = newwin(setting::height+1, 30, 1, setting::width+2); //30 is size for window with score and etc

    curs_set(0);
    nodelay(m_winGame, TRUE);

    keypad(stdscr, TRUE);

    addSpeed();

    m_players.emplace_back(Point{3, 3}, Snake::Direction::down );
    m_players.emplace_back(Point{6, 6}, Snake::Direction::down );
}

bool Game::handleOver(int whoLose)
{
    if(whoLose == 0)
    {
        wmove(m_winGame, setting::width/2, setting::height/2);
        wprintw(m_winGame, "Player 1 is over!");
        wrefresh(m_winGame);
        return true;
    }

    if(whoLose == 1)
    {
        wmove(m_winGame, setting::width/2, setting::height/2);
        wprintw(m_winGame, "Player 2 is over!");
        wrefresh(m_winGame);
        return true;
    }

    return false;
}

void Game::startGame()
{
    spawnSnake();
    spawnFood();

    do
    {
        while (!handleOver(whoLose()))
        {
            displayState();
            updateState();
        }

        printMessageToPlayAgain();

        restartGame();

        stopGame();

    } while(getAnswer() == 'y');

}

int Game::getAnswer()
{
    int answer{};

    do {
        answer = wgetch(m_winGame);
    } while (answer != 'y' && answer != 'n');

    return answer;
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

void Game::restartGame()
{
    m_board = Board{setting::mapPath};

    m_players.clear();

    m_players.emplace_back(Point{3, 3}, Snake::Direction::down );
    m_players.emplace_back(Point{6, 6}, Snake::Direction::down );

    m_food = Food{Point{5, 5}};
}

void Game::spawnSnake()
{
    for(const auto& player: m_players)
    {
        for(const auto& pos: player.getPos())
        {
            m_board.setCellValue(pos, Board::snake);
        }
    }
}

void Game::spawnFood()
{
    m_board.setCellValue(m_food.getPos(), Board::food);
}

void Game::getInputs()
{
    const int desired_duration_ms = m_pauseTime;

    auto start_time = std::chrono::high_resolution_clock::now();

    while (true) {
        inputs.push(getch());

        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

        if (elapsed_time >= desired_duration_ms) {
            break;  // Вихід з циклу, коли час пройшов
        }
    }
}

std::vector<Snake::Direction> Game::parseStack()
{
    std::vector<Snake::Direction> directions(2); // 2 is number of players

    bool dirOne {false};
    bool dirTwo {false};

    while(!inputs.empty())
    {
        int current { inputs.top() };

        if(current != ERR)
        {
            if(current == 'p')
            {
                do {
                    stopGame();

                    current = wgetch(m_winGame);

                } while (current ==
                         'p');  //here we handle case when a player trying to press 'p' more than once consecutively

                addSpeed();
            }
            if(!dirOne && (current == 'w' || current == 's' || current == 'a' || current == 'd'))
            {
                dirOne = true; //we keep the direction we met first for player 1

                directions[0] = parseToDirection(current);
            }
            if(!dirTwo && (current == KEY_UP || current == KEY_DOWN || current == KEY_LEFT || current == KEY_RIGHT))
            {
                dirTwo = true;//we keep the direction we met first for player 2

                directions[1] = parseToDirection(current);
            }
        }
        inputs.pop();
    }

    if(!dirOne)
    {
        directions[0] = Snake::Direction::max_directions;
    }
    if(!dirTwo)
    {
        directions[1] = Snake::Direction::max_directions;
    }

    return directions;
}

void Game::setNewDirections(std::vector<Snake::Direction>& directions)
{
    size_t i{0};

    for(auto& player: m_players)
    {
        if (directions[i] == -player.getDir())
        {
            directions[i] = Snake::Direction::max_directions;
        }
        player.updateDir(directions[i]);
        ++i;
    }

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


void Game::updatePauseTime()
{
    if(m_pauseTime > setting::smallestPauseTime)
        m_pauseTime -= setting::pauseTimeReduceStep;
    addSpeed();
}


void Game::updateState()
{
    m_board.eraseBoard();

    spawnFood();

    getInputs();

    std::vector<Snake::Direction> newDirections { parseStack() };

    setNewDirections(newDirections);

    for(auto& player: m_players)
    {
        if(player.isAte(m_food.getPos())) //if snake ate the food, we make new food
        {
            player.levelUp();                              //we don't call moveSnake() here because we want to increase length of snake
            do {                                            //it means we don't delete last element of snake but just add new head
                m_food.makeRandomPos();

            } while(m_board.isPosWall(m_food.getPos()));//we do this so that the food's position is not a wall's position

            updatePauseTime(); //update speed

        } else {
            player.moveSnake(); //if we don't ate food, we just move snake
        }
    }

    spawnSnake();
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


Snake::Direction Game::parseToDirection(int ch)
{
    switch(ch)
    {
        case 'w':
        case KEY_UP:
            return Snake::Direction::up;
        case 's':
        case KEY_DOWN:
            return Snake::Direction::down;
        case 'a':
        case KEY_LEFT:
            return Snake::Direction::left;
        case 'd':
        case KEY_RIGHT:
            return Snake::Direction::right;
        default:
            return Snake::Direction::max_directions;
    }
}


void Game::printScore()
{
    wmove(m_winScore, 0, 0);
    wprintw(m_winScore, "Player1 : %d",  m_players[0].getScore());

    wmove(m_winScore, 2, 0);
    wprintw(m_winScore, "Player2 : %d",  m_players[1].getScore());
}


bool Game::isPosAnotherSnake(const Point& pos, const Snake& anotherSnake)
{
    for(const auto& anotherPos: anotherSnake.getPos())
    {
        if(pos == anotherPos)
            return true;
    }
    return false;
}


int Game::whoLose()
{
    int counter{0};
    for(const auto& player: m_players)
    {
        for(const auto& pos: player.getPos())
        {
            if(m_board.isPosWall(pos))
                return counter;
        }
        ++counter;
    }

    if(isPosAnotherSnake(m_players[0].getHead(), m_players[1]) || m_players[0].isHitItself())
        return 0;

    if(isPosAnotherSnake(m_players[1].getHead(), m_players[0])|| m_players[1].isHitItself())
        return 1;

    return -1;
}