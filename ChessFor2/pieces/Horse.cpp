#include "Horse.h"

Horse::Horse(PieceColor const &color) : Piece(color) {}

Horse::~Horse() {}

PieceType Horse::getType() const { return PieceType::HORSE; }

std::vector<Position> Horse::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // TODO
  return {};
}
