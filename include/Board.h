#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pieceColors.h"
#include "constants.h"
#include "GetColorTheme.h"
#include "colortheme.h"
#include "Position.h"
#include "LinkedList.h"

class Board
{
public:
    Board();
    void Initialize();
    void Print();
    void Draw(sf::RenderWindow &window, color_theme theme, bool isDeadMode);
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    bool IsCellOccupied(int row, int column);
    int ClearFullRows();
    int gameMatrix[ROW_NUM][COL_NUM];
    bool IsValidMove(int offsetX, int offsetY, const std::map<int, vector<Position>> &cells);

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    ULList<sf::Color> colors;
};
