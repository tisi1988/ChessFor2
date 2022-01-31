#include "King.h"

King::King(PieceColor const &color) : Piece(color) {}

King::~King() {}

PieceType King::getType() const { return PieceType::KING; }

std::vector<Position> King::getMoves(Position const &origin) const {
  // TODO
  return {};
}
