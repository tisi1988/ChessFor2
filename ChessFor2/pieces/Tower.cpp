#include "Tower.h"

Tower::Tower(PieceColor const &color) : Piece(color) {}

Tower::~Tower() {}

PieceType Tower::getType() const { return PieceType::TOWER; }

std::vector<Position> Tower::getMoves(Position const &origin) const {
  // TODO
  return {};
}
