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
  static constexpr int BOARD_SIZE_TILES{8};

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

  /**
   * @brief Check if a given position is valid in the board.
   * @param pos The Position to check.
   * @return true if the position is inside the board. False, otherwise.
   */
  bool isValid(Position const &pos) const;

private:
  void initializePieces();

  mutable std::mutex m_tilesMutex;

  Tile m_tiles[BOARD_SIZE_TILES][BOARD_SIZE_TILES];
};
