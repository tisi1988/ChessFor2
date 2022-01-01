#include "Position.h"

Position::Position(int row, int col) : m_row(row), m_col(col) {}

int Position::getRow() const { return m_row; }

int Position::getCol() const { return m_col; }
