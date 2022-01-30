#pragma once

class Position {
public:
  Position(int x, int y);
  int getX() const;
  int getY() const;

  /**
   * @return the Position as a string.
   */
  std::string toString() const;

private:
  int m_x;
  int m_y;
};
