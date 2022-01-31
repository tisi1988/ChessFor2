#include "Bishop.h"

Bishop::Bishop(PieceColor const &color) : Piece(color) {}

Bishop::~Bishop() {}

PieceType Bishop::getType() const { return PieceType::BISHOP; }

std::vector<Position> Bishop::getMoves(Position const &origin) const {
  // TODO
  return {};
}
