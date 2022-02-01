#pragma once

#include <string>

/**
 * @brief The Position class implements a 2D coordinate.
 */
class Position {
public:
  /**
   * @brief Position constructor.
   * @param x X coordinate.
   * @param y Y coordinate.
   */
  Position(int x, int y);

  /**
   * @return the X coordinate.
   */
  int getX() const;

  /**
   * @return the Y coordinate.
   */
  int getY() const;

  /**
   * @return the Position as a string.
   */
  std::string toString() const;

  bool operator==(Position const &other) const;
  bool operator!=(Position const &other) const;

private:
  int m_x;
  int m_y;
};
