#ifndef PLAYERSETTINGSMENU_H
#define PLAYERSETTINGSMENU_H

#include "Menu.hpp"

class PlayersSettingsChoiceMenu : public Menu
{
public:
    friend class PlayerSettingsMenu;

    explicit PlayersSettingsChoiceMenu(int playerAmounts, int startY, int startX);

    void startMenu() override;

private:
    void setDefaultMenu() override;

    void displayMenu() const override;

    std::vector<const char*> generateChoices(int playersAmount);

    void handleInput() override;

    bool goBack{false};
};
#endif //PLAYERSETTINGSMENU_H
