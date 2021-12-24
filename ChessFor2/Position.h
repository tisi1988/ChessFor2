#pragma once

class Position
{
public:
    Position(int row, int col);
    int getRow() const;
    int getCol() const;

private:
    int m_row;
    int m_col;
};
