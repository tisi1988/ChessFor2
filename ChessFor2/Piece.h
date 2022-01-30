#pragma once

#include "PieceColor.h"
#include "PieceType.h"

class Piece {
public:
  Piece();
  Piece(PieceType const &type, PieceColor const &color);

  PieceType getType() const;
  PieceColor getColor() const;

private:
  PieceType m_type;
  PieceColor m_color;
};
