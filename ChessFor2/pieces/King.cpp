#include "King.h"

King::King(PieceColor const &color) : Piece(color) {}

King::~King() {}

PieceType King::getType() const { return PieceType::KING; }

std::vector<Position> King::getMoves(ChessBoard *board,
                                     Position const &origin) const {
  // King can move horizontally, vertically and diagonally but just 1 step
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, -1},  {0, +1},  {-1, 0},  {+1, 0},
      {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};


  return LinearMovingPiece::getMoves(DIRECTIONS, board, origin, 1);
}
