#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Horse : public Piece {
public:
  Horse(PieceColor const &color);
  ~Horse();

  PieceType getType() const override;
  std::vector<Position> getMoves(Position const &origin) const override;
};
