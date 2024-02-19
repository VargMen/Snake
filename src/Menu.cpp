#include "Menu.hpp"

Menu::Menu()
{
    menus.push_back(new StartMenu{});
    menus.push_back(new SettingsMenu{} );
    activeMenu = menus[START_MENU];

    GraphicsSettings::setThemeValue("../settings.txt");
    activeMenu->applyTheme(GraphicsSettings::m_currentColorPair);
}

Menu::~Menu()
{
    for(auto& menu: menus)
    {
        delete menu;
    }
}

void Menu::start()
{
    while(!activeMenu->goBack)
    {
        updateMenu(); //if newMenu == max_menus it means we don't change menu
                      //otherwise it will change the menu
        activeMenu->applyTheme(GraphicsSettings::m_currentColorPair);
        activeMenu->updateWidthHeight();
        activeMenu->display();
        Event event { activeMenu->handleInput() };
        newMenu = activeMenu->handleEvent(event);
    }
}

void Menu::updateMenu()
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
                savePlayersSettings(PlayerSettingsMenu::m_playerSettingsFilePath);
                erasePlayersMenus();
                isSettingsMenuCreated = false;
            }
            break;

        default: ;
    }
    activeMenu = menus[newMenu];
    newMenu = max_menus;
}

void Menu::createPlayersMenus(int playersAmount)
{
    menus.push_back(new PlayersSelectionMenu{playersAmount});

    PlayerSettingsMenu** plSettingsMenus = PlayerSettingsMenu::generatePlSettingsMenus(playersAmount);

    for(int i{0}; i < playersAmount; ++i)
    {
        menus.push_back(plSettingsMenus[i]);
    }
}

void Menu::savePlayersSettings(const std::string& playerSettingsFile)
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

void Menu::erasePlayersMenus()
{
    for(std::size_t i{settings::playerSettingsMenusBias - 1}; i < menus.size(); ++i)
    {
        delete menus[i];
    }

    menus.erase(menus.begin() + settings::playerSettingsMenusBias - 1, menus.end());
    isSettingsMenuCreated = false;
}
