#include "Game.hpp"

#include "PlayersSettings.hpp"

#include <thread>
#include <algorithm>


Game::Game()
: m_defaultPlayersSettings{PlayersSettings::generatePLayerSettings(settings::playerSettingsFilePath.data(), PlayersSettings::getPlayersAmount("../settings.txt"))}
{
    m_winGame = newwin(settings::height, settings::width, settings::bias_x, settings::bias_y);
    m_winScore = newwin(settings::height, 30, 1 + settings::bias_x, settings::width + 2 + settings::bias_y); //30 is size for window with score and etc

    graphics::setGameColor(m_winGame);
    //graphics::setGameColor(m_winScore);

    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    refresh();
    refreshWindow();
    m_players = m_defaultPlayersSettings;
}

Game::~Game()
{
    wclear(m_winGame);
    wclear(m_winScore);

    wbkgd(m_winGame, graphics::ObjColors::black); //After the game is over, when we return to the menu,
    refreshWindow();                              //part of the playing field remains displayed,
    endwin();                                     //so we do this to make it invisible
}

void Game::startGame()
{
    do {
        std::string loser{};

        do {
            spawnSnake();

            getInputs();
            displayState();
            updateState();
            spawnFood();
            pause();

        } while( (loser = whoLose()) == "" ); //while we not get the name of the loser

        saveScores(getPlayersScores(), "../playersScores.txt");

        printLoser(loser);

        printMessageToPlayAgain();

        restartGame();

    } while(getAnswer() == 'y');
}

void Game::printLoser(const std::string& loser)
{
    mvwprintw(m_winGame, settings::height/2, settings::width/2 - 5, "%s lost!", loser.c_str());
    wrefresh(m_winGame);
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
    wmove(m_winScore, 6 , 0);
    wprintw(m_winScore, "Write 'y' and try again >:D");
    wmove(m_winScore, 8 , 0);
    wprintw(m_winScore, "or 'n' otherwise :(");
    wrefresh(m_winScore);
}

void Game::restartGame()
{
    m_board = Board{settings::mapPath};

    m_players = m_defaultPlayersSettings;

    m_food = Food{Point{5, 5}};
}

void Game::spawnSnake()
{
    int i{0};

    for(auto& player: m_players)
    {
        for(const auto& pos: player.snake().getPos())
        {
            m_board.setCellValue(pos, i);
        }
        ++i;
    }
}

void Game::spawnFood()
{
    m_board.setCellValue(m_food.getPos(), Board::food);
}

void Game::stopGame() {  timeout(-1); }

void Game::resumeGame() { timeout(0); }

void Game::getInputs()
{
    int ch;
    m_inputs.clear();

    while((ch = getch()) != ERR)
    {
        handlePause(ch);
        m_inputs.push_back(ch);
    }
}

void Game::handlePause(int ch)
{
    if(ch == 'p')
    {
        stopGame();

        while(getch() == 'p')
            ;

        resumeGame();
    }
}

void Game::setNewDirections(std::vector<Snake::Direction>& directions)
{
    for(size_t i{0}; i < m_players.size(); ++i)
    {
        if(directions[i] == -m_players[i].snake().getDir())
        {
            directions[i] = Snake::Direction::max_directions;
        }
        m_players[i].snake().updateDir(directions[i]);
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

    printScore();

    makeGameBorder();

    refreshWindow();
}

void Game::makeGameBorder()
{
    wborder(m_winGame, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Game::updatePauseTime()
{
    if(m_pauseTime > settings::smallestPauseTime)
        m_pauseTime -= settings::pauseTimeReduceStep;
}

void Game::pause() const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(m_pauseTime));
}

std::vector<Snake::Direction> Game::handleInput()
{
    std::vector<Snake::Direction> newDirs{};

    for(auto& player: m_players)
    {
        auto keys = player.getKeys();

        bool isKeyExist {false};

        for(auto input: m_inputs)
        {
            auto it { std::find(keys.begin(), keys.end(), input)};
            if(it != keys.end())
            {
                newDirs.emplace_back( static_cast<Snake::Direction>(std::distance(keys.begin(), it)) );
                isKeyExist = true;
                break;
            }
        }

        if(!isKeyExist)
        {
            newDirs.emplace_back( static_cast<Snake::Direction>(Snake::Direction::max_directions) );
        }
    }
    return newDirs;
}

void Game::updateState()
{
    m_board.eraseBoard();

    std::vector<Snake::Direction> newDirs { handleInput() };

    setNewDirections(newDirs);


    for(auto& player: m_players)
    {
        if(player.snake().isAte(m_food.getPos())) //if snake ate the food, we make new food
        {
            updatePauseTime();
            player.snake().levelUp();                              //we don't call moveSnake() here because we want to increase length of snake
            do
            {                                            //it means we don't delete last element of snake but just add new head
                m_food.makeRandomPos();

            } while(m_board.isPosWall(m_food.getPos()));//we do this so that the food's position is not a wall's position

        } else {
            player.snake().moveSnake(); //if we don't ate food, we just move snake
        }
    }
}

void Game::spawnOnBoard(const Point& point, char index)
{
    switch(index)
    {
        case Board::MapSymbols::wall:
            graphics::color_mvwaddch(m_winGame, point.x, point.y,
                                     graphics::ObjColors::wall, graphics::wallSymbol);
            break;
        case Board::MapSymbols::space:
            graphics::color_mvwaddch(m_winGame, point.x, point.y,
                                     graphics::ObjColors::space, graphics::spaceSymbol);
            break;

        case Board::MapSymbols::food:
            graphics::color_mvwaddch(m_winGame, point.x, point.y,
                                     graphics::ObjColors::food, graphics::foodSymbol);
            break;

        default:
            graphics::color_mvwaddch(m_winGame, point.x, point.y,
                                     graphics::ObjColors::firstSnake, m_players[index].getSnakeSymbol());
            std::cout << "\nAboba\n";
    }
}


void Game::printScore()
{
    int bias{0};

    for(int i{0}; i < m_players.size(); i++)
    {
        wmove(m_winScore, i + bias , 0);
        wprintw(m_winScore, "%s: %d", m_players[i].getName().c_str(), m_players[i].getSnakeScore());
        bias += 2;
    }
}


bool Game::isPosAnotherSnake(const Player& testedSnake, const Player& anotherSnake)
{
    Point headTestedSnake { testedSnake.getSnakeHead() };

    for(const auto& anotherPos: anotherSnake.getSnakePos())
    {
        if(headTestedSnake == anotherPos)
            return true;
    }
    return false;
}


std::string_view Game::whoLose()
{
    for(auto& player: m_players) //Here we check that the snakes have not crashed into the wall
    {
        for(const auto& pos: player.getSnakePos())
        {
            if(m_board.isPosWall(pos))
                return player.getName();
        }
    }


    for(auto& testedPlayer: m_players)
    {
        for(const auto& anotherPlayer: m_players)
        {
            if(&testedPlayer == &anotherPlayer)
            {
                if(testedPlayer.snake().isHitItself())
                    return testedPlayer.getName();
                continue;
            }

            if(isPosAnotherSnake(testedPlayer, anotherPlayer)) //it means testedPlayer is crashed into anotherPlayer
            {
                return testedPlayer.getName();
            }
        }
    }
    return "";
}

std::vector<Score> Game::getPlayersScores()
{
    std::vector<Score> playersScores{};
    playersScores.reserve(m_players.size());

    for(const auto& player: m_players)
    {
        playersScores.emplace_back(player.getName(), player.getSnakeScore());
    }

    return playersScores;
}

void Game::saveScores(const std::vector<Score>& newScores, const char* scoresFilePath)
{
    Scores scores{scoresFilePath};
    scores.updateScores(newScores);
}

