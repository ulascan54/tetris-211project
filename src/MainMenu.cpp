#include "MainMenu.h"

MainMenu::MainMenu(float width, float height, std::vector<std::string> menu_items, sf::Color itemc, sf::Color hoverc)
{
    font_color = itemc;
    hover_color = hoverc;
    max_number_of_items = menu_items.size();
    selectedItemIndex = 0;
    menu = new sf::Text[max_number_of_items];
    if (!font.loadFromFile("font/PixelifySans-VariableFont_wght.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    for (int i = 0; i < menu_items.size(); i++)
    {
        menu[i].setFont(font);
        menu[i].setFillColor(font_color);
        menu[i].setString(menu_items[i]);
        menu[i].setPosition(sf::Vector2f(40, height / (max_number_of_items + 1) * (i + 1) + 20));
    }
    menu[0].setFillColor(hover_color);
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < max_number_of_items; i++)
    {
        window.draw(menu[i]);
    }
}

void MainMenu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(font_color);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(hover_color);
    }
}

void MainMenu::MoveDown()
{
    if (selectedItemIndex + 1 < max_number_of_items)
    {
        menu[selectedItemIndex].setFillColor(font_color);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(hover_color);
    }
}

void MainMenu::setFontColor(sf::Color color, sf::Color hoverc)
{
    font_color = color;
    hover_color = hoverc;
    for (int i = 0; i < max_number_of_items; i++)
    {
        menu[i].setFillColor(font_color);
    }
    menu[selectedItemIndex].setFillColor(hover_color);
}
