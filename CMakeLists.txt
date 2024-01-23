cmake_minimum_required(VERSION 3.27)
project(Snake_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(Snake_game main.cpp
        main.cpp
        Snake/Snake.h
        Board/Board.h
        Game/Game.h
        Food/Food.h
        Util/Random.h
        Util/Vector2D.h
        Board/Board.cpp
        settings.h
        Snake/Snake.cpp
        Game/Game.cpp)

target_link_libraries(Snake_game ncurses)