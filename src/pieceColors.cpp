#include "pieceColors.h"

sf::Color darkGrey = sf::Color(26, 31, 40, 255);
sf::Color green = sf::Color(47, 230, 23, 255);
sf::Color red = sf::Color(232, 18, 18, 255);
sf::Color orange = sf::Color(226, 116, 17, 255);
sf::Color yellow = sf::Color(237, 234, 4, 255);
sf::Color purple = sf::Color(166, 0, 247, 255);
sf::Color cyan = sf::Color(21, 204, 209, 255);
sf::Color blue = sf::Color(13, 64, 216, 255);
sf::Color lightBlue = sf::Color(59, 85, 162, 255);
sf::Color darkBlue = sf::Color(44, 44, 127, 255);
sf::Color pink = sf::Color(255, 0, 255, 255);
sf::Color darkPink = sf::Color(255, 0, 127, 255);
sf::Color lightPink = sf::Color(255, 127, 127, 255);
sf::Color lightGreen = sf::Color(127, 255, 127, 255);
sf::Color darkGreen = sf::Color(0, 127, 0, 255);
sf::Color lightRed = sf::Color(255, 127, 127, 255);
sf::Color darkRed = sf::Color(127, 0, 0, 255);
sf::Color lightOrange = sf::Color(255, 127, 0, 255);
sf::Color darkOrange = sf::Color(127, 63, 0, 255);
sf::Color lightYellow = sf::Color(255, 255, 127, 255);
sf::Color darkYellow = sf::Color(127, 127, 0, 255);
sf::Color lightPurple = sf::Color(255, 127, 255, 255);
sf::Color darkPurple = sf::Color(127, 0, 127, 255);
sf::Color lightCyan = sf::Color(127, 255, 255, 255);
sf::Color darkCyan = sf::Color(0, 127, 127, 255);

ULList<sf::Color> GetCellColors()
{
    ULList<sf::Color> colors;
    colors.push_back(darkGrey);
    colors.push_back(green);
    colors.push_back(red);
    colors.push_back(orange);
    colors.push_back(yellow);
    colors.push_back(purple);
    colors.push_back(cyan);
    colors.push_back(blue);
    colors.push_back(lightBlue);
    colors.push_back(darkBlue);
    colors.push_back(pink);
    colors.push_back(darkPink);
    colors.push_back(lightPink);
    colors.push_back(lightGreen);
    colors.push_back(darkGreen);
    colors.push_back(lightRed);
    colors.push_back(darkRed);
    colors.push_back(lightOrange);
    colors.push_back(darkOrange);
    colors.push_back(lightYellow);
    colors.push_back(darkYellow);
    colors.push_back(lightPurple);
    colors.push_back(darkPurple);
    colors.push_back(lightCyan);
    colors.push_back(darkCyan);
    return colors;
}
