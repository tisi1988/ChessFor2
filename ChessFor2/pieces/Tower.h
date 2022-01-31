#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Tower : public Piece {
public:
  Tower(PieceColor const &color);
  ~Tower();

  PieceType getType() const override;
  std::vector<Position> getMoves(Position const &origin) const override;
};
