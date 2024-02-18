#ifndef PLAYERSETTINGSMENU_H
#define PLAYERSETTINGSMENU_H

#include <fstream>
#include <cassert>

#include "BaseMenu.hpp"

#include <iostream>

class PlayerSettingsMenu : public BaseMenu
{
public:

    friend class Menu;

    enum Choices
    {
        NAME,
        MOVEMENT_KEYS,
        SNAKE_COLOR,
        SNAKE_SYMBOL,

        max_choices
    };

    enum SnakeColors
    {
        GREEN,
        BLUE,
        RED,
        YELLOW,
        GRAY,
        ORANGE,
        WHITE,
        BLACK,
        CYAN,
        MAGENTA,

        max_snake_colors
    };

    explicit PlayerSettingsMenu(int playerIndex);

    ~PlayerSettingsMenu() override;

private:

    static std::vector<std::vector<std::string>> parsePlayersSettingFile(const std::string& fileName);

    static PlayerSettingsMenu** generatePlSettingsMenus(int playersAmount);

    Menus handleEvent(const Event& event) override;

    void display() const override;

    void changeValue(int& value, int minValue, int maxValue);

    void changeStringValue(int stringValueIndex, int maxBufferSize);

    std::string getInputStr(int bufferSize);

    void handleChangesValue(int& choice, int minValue, int maxValue);

    void handleChangesStringValue(int stringValueIndex, int maxStrSize);

    void setChoicesValue(const std::vector<std::string>& values);

    int getIndexValue(int index) const override;

    static void setPlayersAmount(int playersAmount) { m_playersAmount = playersAmount; }

private:

    static int m_playersAmount;

    int m_playerIndex{};
    bool m_saveChanges{false};
    static bool m_isSettingSaved;
    static constexpr char* m_colorsStr[] {"Green", "Blue", "Red", "Yellow", "Gray",
                                          "Orange", "White", "Black", "Cyan", "Magenta"};
    int m_colorIndex{1};
};

#endif //PLAYERSETTINGSMENU_H
