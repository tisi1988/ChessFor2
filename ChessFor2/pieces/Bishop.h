#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Bishop : public Piece {
public:
  Bishop(PieceColor const &color);
  ~Bishop();

  PieceType getType() const override;
  std::vector<Position> getMoves(Position const &origin) const override;
};
