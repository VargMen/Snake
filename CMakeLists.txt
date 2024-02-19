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
        src/BaseMenu.cpp
        include/BaseMenu.hpp
        graphics.hpp
        include/Scores.hpp
        src/Scores.cpp
        include/SettingsMenu.hpp
        include/StartMenu.hpp
        src/StartMenu.cpp
        src/SettingsMenu.cpp
        include/PlayerSettingsMenu.hpp
        src/PlayerSettingsMenu.cpp
        include/Menu.hpp
        include/PlayersSelectionMenu.hpp
        src/PlayersSelectionMenu.cpp
        include/PlayersSettings.hpp
        src/PlayersSettings.cpp
        frequentlyUsedVariables.hpp
        frequentlyUsedVariables.cpp
        src/Menu.cpp


)

target_include_directories(Snake_game PUBLIC
                                    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Util/"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries(Snake_game ncurses)