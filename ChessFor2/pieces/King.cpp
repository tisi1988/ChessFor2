#include "King.h"

namespace {
bool isInInitialTile(int row, PieceColor color) {
  static constexpr int BLACK_KING_INIT_ROW{0};
  static constexpr int WHITE_KING_INIT_ROW{7};

  return row == BLACK_KING_INIT_ROW && color == PieceColor::BLACK ||
         row == WHITE_KING_INIT_ROW && color == PieceColor::WHITE;
}
} // namespace

King::King(PieceColor const &color) : LinearMovingPiece(color) {}

King::~King() {}

PieceType King::getType() const { return PieceType::KING; }

std::vector<Position> King::getMoves(ChessBoard *board,
                                     Position const &origin) const {
  // King can move horizontally, vertically and diagonally but just 1 step
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, -1},  {0, +1},  {-1, 0},  {+1, 0},
      {-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

  if (isInInitialTile(origin.getY(), m_color)) {
    // TODO Check for castling!
  }

  return LinearMovingPiece::getMoves(DIRECTIONS, board, origin, 1);
}
