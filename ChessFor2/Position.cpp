#include "Position.h"

Position::Position(int x, int y) : m_x(x), m_y(y) {}

int Position::getX() const { return m_x; }

int Position::getY() const { return m_y; }

std::string Position::toString() const {
  return "[" + std::to_string(m_x) + ", " + std::to_string(m_y) + "]";
}
