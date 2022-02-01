#pragma once

#include "../Position.h"
#include "PieceColor.h"
#include "PieceType.h"

#include <vector>

class ChessBoard;

/**
 * @brief The Piece class implements a generic piece.
 */
class Piece {
public:
  static constexpr int BLACK_PAWN_INIT_ROW{1};
  static constexpr int WHITE_PAWN_INIT_ROW{6};

  /**
   * @brief Piece class constructor.
   * @param color Piece color.
   */
  Piece(PieceColor const &color);

  virtual ~Piece();

  /**
   * @return the Piece color.
   */
  PieceColor getColor() const;

  /**
   * @return the Piece type.
   */
  virtual PieceType getType() const = 0;

  /**
   * @brief Computes the possible destination positions of the Piece based on
   * a given origin Position.
   * @param board The chessboard instance.
   * @param origin Where the Piece is right now.
   * @return the list of possible Position where the Piece can be moved to.
   */
  virtual std::vector<Position> getMoves(ChessBoard *board,
                                         Position const &origin) const = 0;

  /**
   * @brief Factory method to create Pieces.
   * @param type Piece type to create.
   * @param color Piece color to create.
   * @return the new created Piece.
   */
  static Piece *create(PieceType type, PieceColor color);

protected:
  PieceColor m_color;
};
