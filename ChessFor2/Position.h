#pragma once

class Position {
public:
  Position(int row, int col);
  int getX() const;
  int getY() const;

private:
  int m_x;
  int m_y;
};
