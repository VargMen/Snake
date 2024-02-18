#ifndef PLAYERSELECTIONMENU_HPP
#define PLAYERSELECTIONMENU_HPP

#include "BaseMenu.hpp"
#include "PlayerSettingsMenu.hpp"

class PlayersSelectionMenu : public BaseMenu
{
public:

    explicit PlayersSelectionMenu(int playerAmount);

    ~PlayersSelectionMenu() override = default;
private:

    Menus handleEvent(const Event& event) override;

    void display() const override;

    static std::vector<std::string> generateChoices(int playersAmount);
};

#endif //PLAYERSELECTIONMENU_HPP
