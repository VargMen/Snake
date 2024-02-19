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
        PLAYERS_SETTINGS,

        max_choices
    };

    explicit SettingsMenu();

    ~SettingsMenu() override = default;

private:

    static std::vector<int> parseSettingFile(const std::string& fileName);

    void saveSettingsValues(const std::vector<std::variant<int, std::string>>& values,
                            const std::string& settingsFilePath);


    void display() const override;


    void changeValue(int& value, int minValue, int maxValue);

    void handleChangesValue(int& value, int minValue, int maxValue);

    Menus handleEvent(const Event& event) override;

private:
    bool saveChanges{false};
    static const char* m_settingsFilePath;
};

#endif //SETTINGSMENU_HPP
