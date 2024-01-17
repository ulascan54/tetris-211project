#include "Piece.h"
#include <cstdlib>

Piece::Piece()
{
    boardInstance = Board();
    cellSize = CELL_SIZE;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
    customState = 0;
}

void Piece::Draw(int offsetX, int offsetY, sf::RenderWindow &window, bool isKeepedItem, bool isDeadMode)
{
    if (isKeepedItem)
    {
        rowOffset = 0;
        columnOffset = 0;
        Move(0, 1);
        Move(0, 1);
        Move(0, 1);
    }

    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        sf::RectangleShape blockRect(sf::Vector2f(cellSize - 1, cellSize - 1));
        blockRect.setPosition(item.column * cellSize + offsetX, item.row * cellSize + offsetY);
        if (isDeadMode)
        {
            blockRect.setFillColor(colors[rand() % colors.size() + 0]);
        }
        else
        {
            blockRect.setFillColor(colors[id]);
        }

        window.draw(blockRect);
    }
}

void Piece::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

vector<Position> Piece::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Piece::Rotate()
{
    rotationState++;
    if (rotationState == static_cast<int>(cells.size()))
    {
        rotationState = 0;
    }
}

void Piece::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = static_cast<int>(cells.size()) - 1;
    }
}

bool Piece::IsValidMove(int offsetX, int offsetY, Board &board)
{
    vector<Position> newPositions = GetCellPositionsAfterMove(offsetX, offsetY);

    if (!ArePositionsWithinBoard(newPositions, board))
    {
        return false;
    }

    if (ArePositionsOccupied(newPositions, board))
    {
        return false;
    }

    return true;
}

vector<Position> Piece::GetCellPositionsAfterMove(int offsetX, int offsetY)
{
    vector<Position> newPositions;
    for (auto &entry : cells[rotationState])
    {
        newPositions.push_back({entry.row + rowOffset + offsetY, entry.column + columnOffset + offsetX});
    }
    return newPositions;
}

bool Piece::ArePositionsWithinBoard(vector<Position> &positions, Board &board)
{
    int boardWidth = COL_NUM;
    int boardHeight = ROW_NUM;

    return std::all_of(positions.begin(), positions.end(), [boardWidth, boardHeight](Position &pos)
                       { return pos.row >= 0 && pos.row < boardHeight && pos.column >= 0 && pos.column < boardWidth; });
}

bool Piece::ArePositionsOccupied(vector<Position> &positions, Board &board)
{
    return std::any_of(positions.begin(), positions.end(), [&board](Position &pos)
                       { return board.IsCellOccupied(pos.row, pos.column); });
}

void Piece::RotateCustom()
{
    std::map<int, vector<Position>> oldCells = cells;

    vector<Position> centerVector = oldCells[0];

    if (!centerVector.empty())
    {
        Position center = centerVector[centerVector.size() / 2];

        customState = (customState + 1) % 4;

        for (auto &entry : cells)
        {
            int key = entry.first;
            vector<Position> &positions = entry.second;

            for (Position &pos : positions)
            {
                int relativeX = pos.column - center.column;
                int relativeY = pos.row - center.row;

                switch (customState)
                {
                case 1:
                    pos.column = center.column + relativeY;
                    pos.row = center.row - relativeX;
                    break;
                case 2:
                    pos.column = center.column - relativeX;
                    pos.row = center.row - relativeY;
                    break;
                case 3:
                    pos.column = center.column - relativeY;
                    pos.row = center.row + relativeX;
                    break;
                default:
                    break;
                }
            }
        }
        if (!boardInstance.IsValidMove(0, 0, cells))
        {
            cells = oldCells;
        }
    }
    else
    {
        return;
    }
}
