#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Menu.hpp"
#include "PlayersSelectionMenu.hpp"



class SettingsMenu: public Menu
{
public:
    friend class MainMenu;

    enum Choices
    {
        PLAYERS_AMOUNT,
        LEVEL,
        DIFFICULTY,
        PLAYER_SETTINGS,

        max_choices
    };

    explicit SettingsMenu(const std::vector<std::string>& choices);

    void startMenu() override;

private:

    void makePlayersSelectionMenu();

    void displayMenu() const override;

    void changeValue(int& value, int minValue, int maxValue);

    void handleChangesValue(int& value, int minValue, int maxValue);

    void handleEvent(const Event& event) override;

private:

    std::vector<int> m_choicesValue{3, 1, 4}; //here 3 is playersAmount etc
    bool saveChanges{false};
    bool goBack{false};
};
#endif //SETTINGS_HPP
