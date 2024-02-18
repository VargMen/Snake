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
        menus.push_back(new StartMenu{});
        menus.push_back(new SettingsMenu{} );

        activeMenu = menus[START_MENU];
    }

    ~Menu()
    {
        for(auto& menu: menus)
        {
            delete menu;
        }
    }

    void start()
    {
        while(!activeMenu->goBack)
        {
            changeMenu(); //if newMenu == max_menus it means we don't change menu
                          //otherwise it will change the menu

            activeMenu->updateWidthHeight();
            activeMenu->display();
            Event event { activeMenu->handleInput() };
            newMenu = activeMenu->handleEvent(event);
        }
    }

private:

    void changeMenu()
    {
        switch(newMenu)
        {
        case max_menus:
            return;
        case PLAYER_SELECTION_MENU:
                if(!isSettingsMenuCreated)
                {
                    createPlayersMenus(menus[SETTINGS_MENU]->getIntChoiceValue(0));
                    isSettingsMenuCreated = true;
                }
                break;

            case SETTINGS_MENU:
                if(isSettingsMenuCreated)
                {
                    savePlayersSettings("../playersSettings.txt");
                    erasePlayersMenus();
                    isSettingsMenuCreated = false;
                }
                break;

            default: ;
        }
        activeMenu = menus[newMenu];
        newMenu = max_menus;
    }

    void createPlayersMenus(int playersAmount)
    {
        menus.push_back(new PlayersSelectionMenu{playersAmount});

        PlayerSettingsMenu** plSettingsMenus = PlayerSettingsMenu::generatePlSettingsMenus(playersAmount);

        for(int i{0}; i < playersAmount; ++i)
        {
            menus.push_back(plSettingsMenus[i]);
        }
    }

    void savePlayersSettings(const std::string& playerSettingsFile)
    {
        std::fstream playerSettings{ playerSettingsFile };

        for(int i{0}; i < menus[SETTINGS_MENU]->getIntChoiceValue(0); ++i)
        {
            std::string playerLine { "Player " + std::to_string(i + 1) + ':'};

            playerSettings << playerLine << '\n';

            for(int j{0}; j < settings::maxPlayerSettings; ++j)
            {
                playerSettings << menus[i + 3]->m_choices[j] << ": ";

                if(j == 2)
                {
                    playerSettings << menus[i + 3]->getIndexValue(0) << '\n';
                }
                else
                {
                    playerSettings  << menus[i + 3]->getStrChoiceValue(j) << '\n';
                }
            }

            playerSettings << '\n';
        }
    }


    void erasePlayersMenus()
    {
        for(std::size_t i{settings::playerSettingsMenusBias - 1}; i < menus.size(); ++i)
        {
            delete menus[i];
        }

        menus.erase(menus.begin() + settings::playerSettingsMenusBias - 1, menus.end());
        isSettingsMenuCreated = false;
    }

    bool isSettingsMenuCreated {false};
    std::vector<BaseMenu*> menus{};
    Menus newMenu{max_menus};
    BaseMenu* activeMenu{};
};
#endif //MENU_HPP
