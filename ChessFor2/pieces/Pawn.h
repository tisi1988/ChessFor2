#pragma once

#include "Piece.h"
#include "PieceColor.h"

class Pawn : public Piece {
public:
  explicit Pawn(PieceColor const &color);
  ~Pawn();

  PieceType getType() const override;
  std::vector<Position> getMoves(ChessBoard *board,
                                 Position const &origin) const override;

private:
  /**
   * @brief Checks if the Pawn can move forward either one or two tiles.
   * @param moves The list of possible movements forward.
   * @param board The chess board
   * @param origin The Pawn's original position.
   */
  void addFrontMoves(std::vector<Position> &moves, ChessBoard *board,
                     Position const &origin) const;

  /**
   * @brief Checks if the Pawn can kill an enemy piece located at the front-left
   * or front-right of the Pawn's current position.
   * @param moves The list of possible movements forward.
   * @param board The chess board
   * @param origin The Pawn's original position.
   */
  void addKills(std::vector<Position> &moves, ChessBoard *board,
                Position const &origin) const;

  bool checkPossibleKill(ChessBoard *board, Position const &pos) const;

  int m_direction;
};
