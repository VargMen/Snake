cmake_minimum_required(VERSION 3.27)
project(Snake_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Snake_1 main.cpp
        Snake.cpp
        Snake.h
        Board.cpp
        Board.h
        Game.cpp
        Game.h
        Food.cpp
        Food.h
        Random.h)
