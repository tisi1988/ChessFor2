#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Pawn : public Piece {
public:
  Pawn(PieceColor const &color);
  ~Pawn();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
