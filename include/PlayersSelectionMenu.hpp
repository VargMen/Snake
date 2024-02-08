#ifndef PLAYERSLECTIONMENU_H
#define PLAYERSLECTIONMENU_H

#include "Menu.hpp"
#include "PlayerSettingsMenu.hpp"

class PlayersSelectionMenu : public Menu
{
public:

    explicit PlayersSelectionMenu(int playerAmounts, int startY, int startX);

    void startMenu() override;

private:

    void makePlayerSettingsMenu(int playerIndex);

    void handleEvent(const Event& event) override;

    void displayMenu() const override;

    static std::vector<std::string> generateChoices(int playersAmount);

    bool goBack{false};
};
#endif //PLAYERSLECTIONMENU_H
