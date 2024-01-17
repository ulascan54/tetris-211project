#pragma once
#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include "Player.h"
#include "constants.h"

class CustomShapeEditor
{
public:
    CustomShapeEditor(Player *p);
    void run();

private:
    sf::RenderWindow window;
    vector<Position> customShapeCells;
    vector<CustomShape> pieces;
    sf::Text successText;
    sf::Font font;

    Player *player;

    bool istextShown;
    int id;

    void handleEvents();
    bool isWithinGrid(sf::Vector2f &position);
    void render();
};