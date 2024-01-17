#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "constants.h"
#include <iostream>

class MainMenu
{
public:
    MainMenu(float width, float height, std::vector<std::string> menu_items, sf::Color itemc, sf::Color hoverc);
    ~MainMenu();
    sf::Color font_color;
    sf::Color hover_color;

    void setFontColor(sf::Color color, sf::Color hoverc);

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; };
    void setPressedItem(int index) { selectedItemIndex = index; };

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text *menu;
    int max_number_of_items;
};