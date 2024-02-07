#ifndef PLAYERSETTINGSMENU_H
#define PLAYERSETTINGSMENU_H

#include "Menu.hpp"

class PlayersSelectionMenu : public Menu
{
public:
    friend class PlayerSettingsMenu;

    explicit PlayersSelectionMenu(int playerAmounts, int startY, int startX);

    void startMenu() override;

private:

    void displayMenu() const override;

    static std::vector<std::string> generateChoices(int playersAmount);

    bool goBack{false};
};
#endif //PLAYERSETTINGSMENU_H
