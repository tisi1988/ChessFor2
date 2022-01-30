#pragma once

#include "Piece.h"

class Tile {
public:
  Tile();
  explicit Tile(Piece const &piece);
  Tile(Tile const &other);

  Piece getPiece() const;
  void setPiece(Piece const &piece);

  Tile &operator=(Tile const &other);

private:
  Piece m_piece;
};
