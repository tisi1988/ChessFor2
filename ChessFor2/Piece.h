#pragma once

#include "PieceColor.h"
#include "PieceType.h"

/**
 * @brief The Piece class implements a generic piece.
 */
class Piece {
public:
  /**
   * @brief Piece class constructor.
   */
  Piece();

  /**
   * @brief Piece class constructor.
   * @param type Piece type.
   * @param color Piece color.
   */
  Piece(PieceType const &type, PieceColor const &color);

  /**
   * @return the Piece type.
   */
  PieceType getType() const;

  /**
   * @return the Piece color.
   */
  PieceColor getColor() const;

private:
  PieceType m_type;
  PieceColor m_color;
};
