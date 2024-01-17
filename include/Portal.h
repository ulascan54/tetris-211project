#pragma once
#include "Piece.h"
#include <cstdlib>

class Portal
{
public:
    Portal(int width, int height);
    bool IsPieceTouching(Piece &piece);
    void TeleportPiece(Piece &piece, bool isOk);
    void PlaceRandomly(Piece &piece, bool isOk);
    void Draw(sf::RenderWindow &window);

private:
    sf::Vector2i portalPosition;
    int x;
    int y;
    int width;
    int height;
};
