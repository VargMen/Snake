#ifndef MENU_HPP
#define MENU_HPP

#include "StartMenu.hpp"
#include "SettingsMenu.hpp"
#include "PlayersSelectionMenu.hpp"
#include "PlayerSettingsMenu.hpp"

using namespace std::string_literals;

class Menu
{
public:
    Menu()
    {
        startMenu = new StartMenu{ {"Play", "Settings", "Exit"} };
        settingsMenu = new SettingsMenu{  {"Players amount", "Level", "Difficulty", "Players settings"} };
        plSelectionMenu = new PlayersSelectionMenu{};
        plSettingsMenus = PlayerSettingsMenu::generatePlSettingsMenus();
    }

    ~Menu()
    {
        delete startMenu;
        delete settingsMenu;
        delete plSelectionMenu;
        delete[] plSettingsMenus;
    }

    void start()
    {
        activeMenu->start();
    }

private:
    void changeMenu(BaseMenu* newMenu)
    {
        activeMenu = newMenu;
    }

    StartMenu* startMenu{};
    SettingsMenu* settingsMenu{};
    PlayersSelectionMenu* plSelectionMenu{};
    PlayerSettingsMenu** plSettingsMenus{};

    BaseMenu* activeMenu{};
};
#endif //MENU_HPP
