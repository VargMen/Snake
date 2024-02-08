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

    explicit PlayerSettingsMenu(int playerIndex, const std::vector<std::string>& choices);

    void startMenu() override;

private:

    void handleEvent(const Event& event) override;

    void displayMenu() const override;

    void changeValue(int& value, int minValue, int maxValue);

    void changeStringValue(int stringValueIndex, int maxBufferSize);

    std::string getInputStr(int bufferSize);

    void handleChangesValue(int& choice, int minValue, int maxValue);

    void handleChangesStringValue(int stringValueIndex, int maxStrSize);

private:
    int m_playerIndex{};
    bool m_goBack{false};
    bool m_saveChanges{false};

    static constexpr char* m_colorsStr[] {"Green", "Blue", "Red", "Yellow", "Gray",
                                          "Orange", "White", "Black", "Cyan", "Magenta"};
    int colorIndex{0};
    std::vector<std::string> m_choicesValue{"Viktor", "wsad", "Green", "0"};
};

#endif //PLAYERSETTINGSMENU_H
