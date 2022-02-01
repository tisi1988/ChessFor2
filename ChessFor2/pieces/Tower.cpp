#include "Tower.h"

Tower::Tower(PieceColor const &color) : Piece(color) {}

Tower::~Tower() {}

PieceType Tower::getType() const { return PieceType::TOWER; }

std::vector<Position> Tower::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // TODO
  return {};
}
