#pragma once

class Position
{
public:
    Position() = default;
    Position(int row, int column);
    int row;
    int column;
};