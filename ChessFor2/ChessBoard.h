#pragma once

#include "Position.h"
#include "Tile.h"

class ChessBoard {
public:
  ChessBoard();

  Tile getTile(Position const &pos) const;

private:
  void initializePieces();

  Tile m_tiles[8][8];
};
