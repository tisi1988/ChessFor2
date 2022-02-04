#pragma once

#include "ChessBoard.h"
#include "GameResult.h"
#include "Position.h"
#include "pieces/PieceColor.h"

#include <memory>

/**
 * @brief The GameAnalyzer class implements the Chess game analysis.
 * It checks if the game is over, or if the user can castle the king.
 */
class GameAnalyzer {
public:
  /**
   * @brief GameAnalyzer constructor.
   * @param board The board to analyze.
   */
  explicit GameAnalyzer(std::weak_ptr<ChessBoard> board);

  /**
   * @brief Checks if the game is over.
   * @param Player of the current turn.
   * @return the outcome of the match (if any).
   * @see GameResult
   */
  GameResult isGameOver(PieceColor currentPlayer) const;

  /**
   * @brief Checks if a movement is suicidal.
   * @param src Origin position of the movement.
   * @param dst Destination of the movement.
   */
  bool isSuicidalMovement(Position const &src, Position const &dst) const;

  /**
   * @brief Moves a piece from source to destination position.
   * @param src The positon where the piece is moving from.
   * @param dst The positon where the piece is moving to.
   */
  void movePiece(Position const &src, Position const &dst) const;

private:
  std::weak_ptr<ChessBoard> m_board;
};
