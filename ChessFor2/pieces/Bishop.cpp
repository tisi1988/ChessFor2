#include "Bishop.h"

Bishop::Bishop(PieceColor const &color) : LinearMovingPiece(color) {}

Bishop::~Bishop() {}

PieceType Bishop::getType() const { return PieceType::BISHOP; }

std::vector<Position> Bishop::getMoves(ChessBoard *board,
                                       Position const &origin) const {
  // Bsihop can move only diagonally
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

  return LinearMovingPiece::getMoves(DIRECTIONS, board, origin);
}
