#include "Queen.h"

Queen::Queen(PieceColor const &color) : Piece(color) {}

Queen::~Queen() {}

PieceType Queen::getType() const { return PieceType::QUEEN; }

std::vector<Position> Queen::getMoves(Position const &origin) const {
  // TODO
  return {};
}
