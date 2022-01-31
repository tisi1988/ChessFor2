#pragma once

#include "Position.h"
#include "Tile.h"

#include <mutex>

/**
 * @brief The ChessBoard class models the chess board.
 *
 * The board is made of a fixed amount (8x8) of Tiles.
 */
class ChessBoard {
public:
  /**
   * @brief ChessBoard class constructor.
   */
  ChessBoard();

  /**
   * @brief Returns a Tile for a given info.
   * @param pos The position to get the tile from.
   * @return the Tile for the given position.
   */
  Tile *getTile(Position const &pos);

private:
  void initializePieces();

  mutable std::mutex m_tilesMutex;

  static constexpr int BOARD_SIZE_TILES{8};
  Tile m_tiles[BOARD_SIZE_TILES][BOARD_SIZE_TILES];
};
