#pragma once

#include "Position.h"
#include "Tile.h"

#include <mutex>

class ChessBoard {
public:
  ChessBoard();

  Tile getTile(Position const &pos) const;

private:
  void initializePieces();

  mutable std::mutex m_tilesMutex;
  Tile m_tiles[8][8];
};
