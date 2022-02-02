#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Queen : public Piece {
public:
  explicit Queen(PieceColor const &color);
  ~Queen();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
