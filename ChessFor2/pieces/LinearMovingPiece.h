#pragma once

#include "../ChessBoard.h"
#include "Piece.h"

/**
 * @brief The LinearMovingPiece class implements a Piece
 * that moves in a linear manner (horizontal, vertical or diagonally).
 */
class LinearMovingPiece : public Piece {
protected:
  /**
   * @brief LinearMovingPiece constructor.
   * @param color The piece color.
   */
  explicit LinearMovingPiece(PieceColor const &color);

  /**
   * @brief Computes the possible moves of the pieces. It takes into account
   * board edges, friendly or enemy pieces and the step limit of the piece.
   * @param directions List of directions the piece can move towards. These
   * directions are represented as row and column deltas.
   * @param board The board where the piece is playing.
   * @param origin The original Position of the Piece.
   * @param maxSteps The maximum amount of steps the piece can move. By default
   * is the chessboard width. For instance, a Tower has no limits but the King
   * can move only one Tile.
   * @return the list of possible Position where the Piece can be moved to.
   */
  std::vector<Position>
  getMoves(const std::vector<std::pair<int, int>> &directions,
           ChessBoard *board, Position const &origin,
           int maxSteps = ChessBoard::BOARD_SIZE_TILES) const;
};
