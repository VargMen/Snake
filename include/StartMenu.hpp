#ifndef STARTMENU_H
#define STARTMENU_H

#include "BaseMenu.hpp"
#include "Game.hpp"
#include "SettingsMenu.hpp"


constexpr char* snake {   "\n"
                          " .d8888b.                    888               \n"
                          "d88P  Y88b                   888               \n"
                          "Y88b.                        888               \n"
                          " \"Y888b.   88888b.   8888b.  888  888  .d88b.  \n"
                          "    \"Y88b. 888 \"88b     \"88b 888 .88P d8P  Y8b \n"
                          "      \"888 888  888 .d888888 888888K  88888888 \n"
                          "Y88b  d88P 888  888 888  888 888 \"88b Y8b.     \n"
                          " \"Y8888P\"  888  888 \"Y888888 888  888  \"Y8888  \n"
                          "                                               \n"
                          "                                               \n"
                          "                                               "
                     };


class StartMenu : public BaseMenu
{
public:

    enum Choices
    {
        PLAY,
        SETTINGS,
        EXIT,

        max_choices
    };

    explicit StartMenu();

    ~StartMenu() override = default;
private:

    Menus handleEvent(const Event& event) override;

    static bool makeGame();

    void display() const override;

};

#endif //STARTMENU_H
