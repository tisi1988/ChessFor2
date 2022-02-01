#include "Horse.h"

#include "../ChessBoard.h"

Horse::Horse(PieceColor const &color) : Piece(color) {}

Horse::~Horse() {}

PieceType Horse::getType() const { return PieceType::HORSE; }

std::vector<Position> Horse::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // Horses move in an 'L' shape
  // This list contains the relative position movement
  static const std::vector<std::pair<int, int>> MOVES_DELTAS = {
      {-2, -1}, {-2, +1}, {-1, +2}, {+1, +2},
      {+2, +1}, {+2, -1}, {+1, -2}, {-1, -2}};

  std::vector<Position> moves;

  for (auto &&[rowDelta, colDelta] : MOVES_DELTAS) {
    Position const p =
        Position(origin.getX() + rowDelta, origin.getY() + colDelta);

    if (!board->isValidPosition(p)) {
      continue;
    }

    // Discard if there's a piece of same color
    if (!board->getTile(p)->isEmpty() &&
        board->getTile(p)->getPiece()->getColor() == m_color) {
      continue;
    }

    moves.push_back(p);
  }

  return moves;
}
