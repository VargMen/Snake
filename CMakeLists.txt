cmake_minimum_required(VERSION 3.27)
project(Snake_game)

set(CMAKE_CXX_STANDARD 17) #i use 17 standard because i use std::uniform_int_distribution in Random.hpp

add_executable(Snake_game main.cpp
        src/Game.cpp
        src/Snake.cpp
        include/Food.hpp
        include/Game.hpp
        include/Snake.hpp
        Util/Random.hpp
        Util/Point.hpp
        settings.hpp
        include/Board.hpp
        src/Board.cpp
        src/Menu.cpp
        include/Menu.hpp


)

target_include_directories(Snake_game PUBLIC
                                    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Util/"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries(Snake_game ncurses)