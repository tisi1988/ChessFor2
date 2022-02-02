#include "Queen.h"

Queen::Queen(PieceColor const &color) : LinearMovingPiece(color) {}

Queen::~Queen() {}

PieceType Queen::getType() const { return PieceType::QUEEN; }

std::vector<Position> Queen::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // Queen can move horizontally, vertically and diagonally
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, -1},  {0, +1},  {-1, 0},  {+1, 0},
      {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

  return LinearMovingPiece::getMoves(DIRECTIONS, board, origin);
}
