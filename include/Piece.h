#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Position.h"
#include "pieceColors.h"
#include "constants.h"
#include "Board.h"
#include "LinkedList.h"

class Piece
{
public:
    Piece();
    void Draw(int offsetX, int offsetY, sf::RenderWindow &window, bool isKeepedItem, bool isDeadMode);
    void Move(int rows, int columns);
    vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    bool IsValidMove(int offsetX, int offsetY, Board &board);
    int id;
    std::map<int, vector<Position>> cells;
    void RotateCustom();

private:
    Board boardInstance;
    int customState;
    int cellSize;
    int rotationState;
    ULList<sf::Color> colors;
    int rowOffset;
    int columnOffset;

    vector<Position> GetCellPositionsAfterMove(int offsetX, int offsetY);
    bool ArePositionsWithinBoard(vector<Position> &positions, Board &board);
    bool ArePositionsOccupied(vector<Position> &positions, Board &board);
};
