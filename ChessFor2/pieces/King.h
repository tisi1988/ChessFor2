#pragma once

#include "Piece.h"
#include "PieceColor.h"

class King : public Piece {
public:
  explicit King(PieceColor const &color);
  ~King();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;
};
