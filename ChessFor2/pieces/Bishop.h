#pragma once

#include "LinearMovingPiece.h"
#include "PieceColor.h"

class Bishop : public LinearMovingPiece {
public:
  explicit Bishop(PieceColor const &color);
  ~Bishop();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
