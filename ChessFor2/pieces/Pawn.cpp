#include "Pawn.h"

#include "../ChessBoard.h"

Pawn::Pawn(PieceColor const &color)
    : Piece(color), m_direction(color == PieceColor::WHITE ? -1 : 1) {}

Pawn::~Pawn() {}

PieceType Pawn::getType() const { return PieceType::PAWN; }

std::vector<Position> Pawn::getMoves(ChessBoard *board,
                                     Position const &origin) const {
  std::vector<Position> moves;

  Position const frontTile =
      Position(origin.getX() + 1 * m_direction, origin.getY());

  // If there's no piece on that position, it can move there
  if (board->isValidPosition(frontTile) &&
      !board->getTile(frontTile)->getPiece()) {
    moves.push_back(frontTile);
  }

  return moves;
}
