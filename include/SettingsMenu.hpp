#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include "BaseMenu.hpp"
#include "PlayersSelectionMenu.hpp"



class SettingsMenu: public BaseMenu
{
public:
    friend class StartMenu;

    enum Choices
    {
        PLAYERS_AMOUNT,
        LEVEL,
        DIFFICULTY,
        PLAYER_SETTINGS,

        max_choices
    };

    explicit SettingsMenu(const std::vector<std::string>& choices);

    void start() override;

private:

    void display() const override;

    void changeValue(int& value, int minValue, int maxValue);

    void handleChangesValue(int& value, int minValue, int maxValue);

    void handleEvent(const Event& event) override;

private:

    std::vector<int> m_choicesValue{3, 1, 4}; //here 3 is playersAmount etc
    bool saveChanges{false};
    bool goBack{false};
};
#endif //SETTINGSMENU_HPP
