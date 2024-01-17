#include "Board.h"
#include "Pieces.h"
#include "constants.h"

Board::Board()
{
    numRows = ROW_NUM;
    numCols = COL_NUM;
    cellSize = CELL_SIZE;
    Initialize();
    colors = GetCellColors();
}

void Board::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            gameMatrix[row][column] = 0;
        }
    }
}

void Board::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            std::cout << gameMatrix[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::Draw(sf::RenderWindow &window, color_theme theme, bool isDeadMode)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = gameMatrix[row][column];
            sf::RectangleShape cellRect(sf::Vector2f(cellSize - 1, cellSize - 1));
            cellRect.setPosition(column * cellSize + SOLOGAMEMODE_POSITION_X, row * cellSize + SOLOGAMEMODE_POSITION_Y);
            if (isDeadMode)
            {
                cellRect.setFillColor(gameMatrix[row][column] == 0 ? getColor(theme, BOARDCOLOR) : colors[rand() % colors.size()]);
            }
            else
            {
                cellRect.setFillColor(gameMatrix[row][column] == 0 ? getColor(theme, BOARDCOLOR) : colors[cellValue]);
            }

            window.draw(cellRect);
        }
    }
}

bool Board::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false;
    }
    return true;
}

bool Board::IsCellEmpty(int row, int column)
{
    if (gameMatrix[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Board::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Board::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        if (gameMatrix[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Board::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        gameMatrix[row][column] = 0;
    }
}

void Board::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++)
    {
        gameMatrix[row + numRows][column] = gameMatrix[row][column];
        gameMatrix[row][column] = 0;
    }
}

bool Board::IsCellOccupied(int row, int column)
{
    return gameMatrix[row][column] != 0;
}

bool Board::IsValidMove(int offsetX, int offsetY, const std::map<int, vector<Position>> &cells)
{

    const int boardRows = ROW_NUM;
    const int boardColumns = COL_NUM;

    for (const auto &entry : cells)
    {
        const vector<Position> &positions = entry.second;

        for (const Position &pos : positions)
        {
            int newRow = pos.row + offsetY;
            int newColumn = pos.column + offsetX;

            if (newRow < 0 || newRow >= boardRows || newColumn < 0 || newColumn >= boardColumns)
            {
                return false;
            }
        }
    }

    return true;
}