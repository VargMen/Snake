#ifndef PLAYERSETTINGSMENU_H
#define PLAYERSETTINGSMENU_H

#include "Menu.hpp"

class PlayerSettingsMenu : public Menu
{
public:
    enum Choices
    {
        NAME,
        MOVEMENT_KEYS,
        SNAKE_SYMBOL,
        SNAKE_COLOR,

        max_choices
    };

    explicit PlayerSettingsMenu(const std::vector<std::string>& choices);

    void startMenu() override;

private:

    void displayMenu() const override;

    void changeValue(int& value, int minValue, int maxValue);

    void changeStringValue(std::string& strValue);

    void handleChangesValue(int& value, int minValue, int maxValue);


    bool goBack{false};

};
#endif //PLAYERSETTINGSMENU_H
