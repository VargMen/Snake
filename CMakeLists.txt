cmake_minimum_required(VERSION 3.27)
project(Snake_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(Snake_game main.cpp
        src/Game.cpp
        src/Snake.cpp
        include/Food.hpp
        include/Game.hpp
        include/Snake.hpp
        Util/Random.hpp
        Util/Point.hpp
        settings.h
        include/Board.hpp
        src/Board.cpp
)

target_link_libraries(Snake_game ncurses)