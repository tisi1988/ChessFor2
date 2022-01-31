#pragma once

#include "TileStatus.h"

class Piece;

/**
 * @brief The Tile class implements a single tile on the chess board.
 */
class Tile {
public:
  /**
   * @brief Tile class constructor.
   */
  Tile();

  /**
   * @brief Tile class constructor.
   * @param piece The Piece the Tile constains.
   */
  explicit Tile(Piece *piece);

  /**
   * @brief Tile copy constructor.
   * @param other The Tile to copy.
   */
  Tile(Tile const &other);

  /**
   * @return the Piece inside the Tile.
   */
  Piece *getPiece() const;

  /**
   * @brief Updates the Piece inside the Tile.
   * @param piece The new Piece.
   */
  void setPiece(Piece *piece);

  /**
   * @return true if the Tile is empty, false otherwise.
   */
  bool isEmpty() const;

  /**
   * @return the Tile status.
   */
  TileStatus getStatus() const;

  /**
   * @brief Sets a new status on the Tile.
   * @param status The new status.
   */
  void setStatus(TileStatus status);

  /**
   * @brief Assign operator.
   * @param other The Tile to assign from.
   * @return the assigned Tile.
   */
  Tile &operator=(Tile const &other);

private:
  Piece *m_piece{nullptr};
  TileStatus m_status{TileStatus::NONE};
};
