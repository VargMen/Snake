#include "Game.hpp"

#include <thread>
#include <algorithm>

Game::Game()
{
    initscr();
    noecho();
    cbreak();
    m_winGame = newwin(settings::height+1, settings::width+1, 0, 0);
    m_winScore = newwin(settings::height+1, 30, 1, settings::width+2); //30 is size for window with score and etc

    curs_set(0);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    setPlayers();
}

bool Game::handleOver(int whoLose)
{
    if(whoLose == 0)
    {
        wmove(m_winGame, settings::height/2, settings::width/2);
        wprintw(m_winGame, "Player 1 is over!");
        wrefresh(m_winGame);
        return true;
    }

    if(whoLose == 1)
    {
        wmove(m_winGame, settings::height/2, settings::width/2);
        wprintw(m_winGame, "Player 2 is over!");
        wrefresh(m_winGame);
        return true;
    }

    return false;
}

void Game::startGame()
{
    spawnFood();

    do
    {
        while (true)
        {
            spawnSnake();

            displayState();
            updateState();
            spawnFood();
        }

        printMessageToPlayAgain();

        restartGame();

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
    wmove(m_winScore, 5 , 0);
    wprintw(m_winScore, "Write 'y' and try again >:D");
    wmove(m_winScore, 7 , 0);
    wprintw(m_winScore, "or 'n' otherwise :(");
    wrefresh(m_winScore);
}

void Game::restartGame()
{
    m_board = Board{settings::mapPath};

    m_players.clear();

    m_food = Food{Point{5, 5}};
}

void Game::spawnSnake()
{
    for(auto& player: m_players)
    {
        for(const auto& pos: player.snake().getPos())
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
    int ch;

    m_inputs.clear();

    while((ch = getch()) != ERR)
    {
        m_inputs.push_back(ch);
    }
}


void Game::setNewDirections(std::vector<Snake::Direction>& directions)
{
    for(int i{0}; i < directions.size(); ++i)
    {
        mvwprintw(m_winScore, 0, 0, "%s", Snake::printDir(directions[i]).c_str());
        wrefresh(m_winScore);
    }

    size_t i{0};

    for(auto& player: m_players)
    {
        if (directions[i] == -player.snake().getDir())
        {
            directions[i] = Snake::Direction::max_directions;
        }
        player.snake().updateDir(directions[i]);
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


    for (int i {0}; i < settings::height; ++i)
    {
        for (int j {0}; j < settings::width; ++j)
        {
            spawnOnBoard(Point{i, j}, static_cast<char>(m_board.getCellValue( Point{i, j} )));
        }
    }

    //printScore();

    refreshWindow();
}


void Game::updatePauseTime()
{
    if(m_pauseTime > settings::smallestPauseTime)
        m_pauseTime -= settings::pauseTimeReduceStep;
}

void Game::handleInput(std::vector<Snake::Direction>& newDirs)
{
    int j{0};
    for(auto& player: m_players)
    {
        auto keys = player.getKeys();
        wmove(m_winScore, 5 + j, 0);
        for(int i{0}; i < 4; ++i)
        {
            wprintw(m_winScore, "%c ", keys[i]);
        }
        ++j;
        wrefresh(m_winScore);

        bool isKeyExist {false};

        for(auto input: m_inputs)
        {
            int i{0};
            for(; i < keys.size(); ++i)
            {
                if(input == keys[i])
                {
                    isKeyExist = true;
                    newDirs.emplace_back( static_cast<Snake::Direction>(i) );
                    break;
                }
            }
        }
        if(!isKeyExist)
        {
            newDirs.emplace_back( static_cast<Snake::Direction>(Snake::Direction::max_directions) );
        }
    }
}

void Game::updateState()
{
    m_board.eraseBoard();

    getInputs();

    std::vector<Snake::Direction> newDirs(settings::playersAmount);

    handleInput(newDirs);


    setNewDirections(newDirs);

    for(auto& player: m_players)
    {
        if(player.snake().isAte(m_food.getPos())) //if snake ate the food, we make new food
        {
            player.snake().levelUp();                              //we don't call moveSnake() here because we want to increase length of snake
            do {                                            //it means we don't delete last element of snake but just add new head
                m_food.makeRandomPos();

            } while(m_board.isPosWall(m_food.getPos()));//we do this so that the food's position is not a wall's position

            updatePauseTime(); //update speed

        } else {
            //player.snake().moveSnake(); //if we don't ate food, we just move snake
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
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


void Game::printScore()
{
    wmove(m_winScore, 0, 0);
    wprintw(m_winScore, "Player1 : %d",  m_players[0].snake().getScore());

    wmove(m_winScore, 2, 0);
    wprintw(m_winScore, "Player2 : %d",  m_players[1].snake().getScore());
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
    for(auto& player: m_players)
    {
        for(const auto& pos: player.snake().getPos())
        {
            if(m_board.isPosWall(pos))
                return counter;
        }
        ++counter;
    }

    if(isPosAnotherSnake(m_players[0].snake().getHead(), m_players[1].snake()) || m_players[0].snake().isHitItself())
        return 0;

    if(isPosAnotherSnake(m_players[1].snake().getHead(), m_players[0].snake())|| m_players[1].snake().isHitItself())
        return 1;

    return -1;
}

void Game::setPlayersKeys()
{
    m_players[0].setKeys(settings::allKeys[0]);
    m_players[1].setKeys(settings::allKeys[1]);
}

void Game::setPlayers()
{
    m_players.emplace_back(Point{3, 3}, Snake::Direction::down);
    m_players.emplace_back(Point{6, 6}, Snake::Direction::down);
    setPlayersKeys();
}