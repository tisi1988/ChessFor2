#pragma once

#include "ChessBoard.h"
#include "GameResult.h"
#include "Position.h"
#include "pieces/Piece.h"
#include "pieces/PieceColor.h"

#include <memory>
#include <unordered_map>

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
  void movePiece(Position const &src, Position const &dst);

  /**
   * @brief Computes the possible destination positions of the Piece present
   * on a given position.
   * @param origin Where the Piece is right now.
   * @return the list of possible Position where the Piece can be moved to. If
   * the given position is empty, returns an empty list of movements.
   */
  std::vector<Position> getMoves(Position const &origin) const;

private:
  void initializeRemainingPieces();
  void computeAdditionalMovesPawn(std::vector<Position> &pieceMoves,
                                  Position const &origin) const;
  void computeAdditionalMovesKing(std::vector<Position> &pieceMoves,
                                  Position const &origin) const;
  bool isEnemyPieceOnPosition(PieceColor playing, Position const &pos) const;

  std::weak_ptr<ChessBoard> m_board;

  /**
   * @brief The PieceHasher struct implement
   * a hash function for Piece.
   */
  struct PieceHasher {
    std::size_t operator()(Piece *p) const {
      // A piece can be identified by its color and type
      return static_cast<int>(p->getColor()) * 10 +
             static_cast<int>(p->getType());
    }
  };

  /// This is an index of the remaining pieces for each user
  std::unordered_map<Piece *, Position, PieceHasher> m_piecesByPlayer[2];
};
