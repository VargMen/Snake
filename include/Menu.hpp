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
    Menu();
    ~Menu();

    void start();

private:

    void updateMenu();


    void createPlayersMenus(int playersAmount);

    void savePlayersSettings(const std::string& playerSettingsFile);

    void erasePlayersMenus();

private:
    bool isSettingsMenuCreated {false};
    std::vector<BaseMenu*> menus{};
    Menus newMenu{max_menus};
    BaseMenu* activeMenu{};
};
#endif //MENU_HPP
