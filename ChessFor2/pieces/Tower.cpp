#include "Tower.h"

#include "../ChessBoard.h"

Tower::Tower(PieceColor const &color) : LinearMovingPiece(color) {}

Tower::~Tower() {}

PieceType Tower::getType() const { return PieceType::TOWER; }

std::vector<Position> Tower::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // Towers move horizontally and vertically
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

  return LinearMovingPiece::getMoves(DIRECTIONS, board, origin);
}
