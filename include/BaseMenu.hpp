#ifndef BASEMENU_H
#define BASEMENU_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <variant>

#include "GraphicsSettings.hpp"

enum Event
{
    ENTER_PRESSED,
    ESC_PRESSED,
    SPACE_PRESSED,

    max_events
};

enum Menus
{
    START_MENU,
    SETTINGS_MENU,
    PLAYER_SELECTION_MENU,
    PlAYERS_SETTINGS_MENU,

    max_menus = 99//I don't think there will be a game with more than 96 players
};

class BaseMenu
        {
public:
    friend class Menu;

    explicit BaseMenu();

    virtual ~BaseMenu() = default;

protected:

    virtual void setDefault();



    virtual void display() const = 0;

    void clearWindow();

    void updateWidthHeight();



    virtual Event handleInput();

    virtual Menus handleEvent(const Event& event) = 0;



    int& getIntChoiceValue(int index);

    int getConstIntChoiceValue(int index) const;

    std::string& getStrChoiceValue(int index);

    std::string getConstStrChoiceValue(int index) const;



    virtual int getIndexValue(int value) const { return -1; };



    void applyTheme(short themeIndex);

protected:

    bool goBack{};
    int m_width{};
    int m_height{};
    WINDOW *m_win{};
    std::vector<std::string> m_choices{};
    std::vector<std::variant<int, std::string>> m_choicesValues{};
    int indexValue{};
    int m_highlight{};
    int m_currentChoice{-1};
};


#endif //BASEMENU_H
