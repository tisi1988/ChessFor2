#pragma once

#include "Piece.h"
#include "PieceColor.h"

class King : public Piece {
public:
  King(PieceColor const &color);
  ~King();

  PieceType getType() const override;
  std::vector<Position> getMoves(Position const &origin) const override;
};
