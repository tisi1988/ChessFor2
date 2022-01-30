#include "Position.h"

Position::Position(int row, int col) : m_x(row), m_y(col) {}

int Position::getX() const { return m_x; }

int Position::getY() const { return m_y; }
