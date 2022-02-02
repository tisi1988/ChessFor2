#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Horse : public Piece {
public:
  explicit Horse(PieceColor const &color);
  ~Horse();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
