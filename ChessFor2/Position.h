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

  /**
   * @brief Check if both coordinates of position are in range.
   * @param min The minimum value of each coordinate.
   * @param max The maximum value of each coordinate.
   * @return true if both coordinates of position are in range. False,
   * otherwise.
   */
  bool inRange(int min, int max) const;

private:
  int m_x;
  int m_y;
};
