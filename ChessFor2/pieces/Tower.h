#pragma once

#include "LinearMovingPiece.h"
#include "PieceColor.h"

class Tower : public LinearMovingPiece {
public:
  explicit Tower(PieceColor const &color);
  ~Tower();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
