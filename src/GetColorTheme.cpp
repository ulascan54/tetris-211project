#include <SFML/Graphics.hpp>
#include "GetColorTheme.h"
#include "colortheme.h"

sf::Color getColor(color_theme theme, color_type type)
{
    if (theme == LIGHT)
    {
        if (type == FONT)
        {
            return sf::Color::Black;
        }
        else if (type == BOARDCOLOR)
        {
            sf::Color lightGray(200, 200, 200);
            return lightGray;
        }
        else if (type == BACKGROUND)
        {
            return sf::Color::White;
        }
        else if (type == BORDER)
        {
            return sf::Color::Black;
        }
        else if (type == TITLE)
        {
            return sf::Color::Magenta;
        }
        else if (type == MENUHOVER)
        {
            return sf::Color::Red;
        }
        else
        {
            throw std::invalid_argument("Invalid color type");
        }
    }
    else if (theme == DARK)
    {
        if (type == FONT)
        {
            return sf::Color::White;
        }
        else if (type == BOARDCOLOR)
        {
            sf::Color darkgray(50, 50, 50);
            return darkgray;
        }
        else if (type == BACKGROUND)
        {
            return sf::Color::Black;
        }
        else if (type == BORDER)
        {
            return sf::Color::White;
        }
        else if (type == TITLE)
        {
            return sf::Color::Cyan;
        }
        else if (type == MENUHOVER)
        {
            return sf::Color::Red;
        }
        else
        {
            throw std::invalid_argument("Invalid color type");
        }
    }
    else if (theme == RETRO)
    {
        if (type == FONT)
        {

            return sf::Color(255, 0, 255);
        }
        else if (type == BOARDCOLOR)
        {
            sf::Color lightGray(255, 255, 255);
            return lightGray;
        }
        else if (type == BACKGROUND)
        {

            return sf::Color(50, 0, 50);
        }
        else if (type == BORDER)
        {

            return sf::Color(255, 0, 255);
        }
        else if (type == TITLE)
        {

            return sf::Color(255, 192, 203);
        }
        else if (type == MENUHOVER)
        {
            return sf::Color::Red;
        }
        else
        {
            throw std::invalid_argument("Invalid color type");
        }
    }
    else if (theme == DEADLY)
    {
        if (type == FONT)
        {

            return sf::Color(155, 0, 0);
        }
        else if (type == BOARDCOLOR)
        {

            return sf::Color(77, 0, 0);
        }
        else if (type == BACKGROUND)
        {

            return sf::Color::Black;
        }
        else if (type == BORDER)
        {

            return sf::Color(77, 0, 0);
        }
        else if (type == TITLE)
        {

            return sf::Color(102, 0, 0);
        }
        else if (type == MENUHOVER)
        {

            return sf::Color(102, 0, 0);
        }
        else
        {
            throw std::invalid_argument("Invalid color type");
        }
    }

    else
    {
        throw std::invalid_argument("Invalid color type");
    }
}