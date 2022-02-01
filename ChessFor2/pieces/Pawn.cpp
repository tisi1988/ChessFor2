#include "Pawn.h"

#include "../ChessBoard.h"

namespace {
bool isInInitialTile(int row, PieceColor color) {
  return row == Piece::BLACK_PAWN_INIT_ROW && color == PieceColor::BLACK ||
         row == Piece::WHITE_PAWN_INIT_ROW && color == PieceColor::WHITE;
}
} // namespace

Pawn::Pawn(PieceColor const &color) : Piece(color) {}

Pawn::~Pawn() {}

PieceType Pawn::getType() const { return PieceType::PAWN; }

std::vector<Position> Pawn::getMoves(ChessBoard *board,
                                     Position const &origin) const {
  std::vector<Position> dest;
  dest.push_back(Position(origin.getX() + 1 * m_direction, origin.getY()));

  // Pawns can move 2 tiles if their in the initial tile
  if (isInInitialTile(origin.getX(), m_color)) {
    dest.push_back(Position(origin.getX() + 2 * m_direction, origin.getY()));
  }

  return dest;
}
