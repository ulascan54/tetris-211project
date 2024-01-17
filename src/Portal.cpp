#include "Portal.h"

Portal::Portal(int width, int height)
    : width(width), height(height), x(rand() % COL_NUM), y(rand() % ROW_NUM / 2 + 5)
{
}

bool Portal::IsPieceTouching(Piece &piece)
{
    vector<Position> piecePositions = piece.GetCellPositions();
    for (Position &pos : piecePositions)
    {
        if (pos.row == y && pos.column == x)
        {
            return true;
        }
    }
    return false;
}

void Portal::TeleportPiece(Piece &piece, bool isOk)
{
    PlaceRandomly(piece, isOk);
}

void Portal::PlaceRandomly(Piece &piece, bool isOk)
{
    int boardWidth = COL_NUM;
    int boardHeight = ROW_NUM / 2;

    if (isOk)
    {
        do
        {
            x = rand() % boardWidth;
            y = rand() % boardHeight + 5;
        } while (IsPieceTouching(piece));
    }
    else
    {
        x = -100;
        y = -100;
    }
}

void Portal::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape portalShape(sf::Vector2f(CELL_SIZE, 5));
    portalShape.setPosition(SOLOGAMEMODE_POSITION_X + x * CELL_SIZE, SOLOGAMEMODE_POSITION_Y + y * CELL_SIZE);
    portalShape.setFillColor(sf::Color::Red);

    window.draw(portalShape);
}
