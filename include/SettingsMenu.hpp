#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Menu.hpp"
#include "PlayersSettingsChoiceMenu.hpp"

class SettingsMenu: public Menu
{
public:
    friend class MainMenu;

    enum Choices
    {
        PLAYERS_AMOUNT,
        LEVEL,
        DIFFICULTY,

        max_choices
    };

    explicit SettingsMenu(const std::vector<const char *>& choices);

    void startMenu() override;

private:

    void setDefaultMenu() override;

    void displayMenu() const override;

    void handleInput() override;

    void changeValue(int& value, int minValue, int maxValue);

    void handleChangesValue(int& value, int minValue, int maxValue);

private:

    std::vector<int> m_choicesValue{3, 1, 4}; //here 3 is playersAmount etc
    bool saveChanges{false};
    bool goBack{false};
};
#endif //SETTINGS_HPP
