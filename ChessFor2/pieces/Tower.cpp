#include "Tower.h"

#include "../ChessBoard.h"

Tower::Tower(PieceColor const &color) : Piece(color) {}

Tower::~Tower() {}

PieceType Tower::getType() const { return PieceType::TOWER; }

std::vector<Position> Tower::getMoves(ChessBoard *board,
                                      Position const &origin) const {
  // Towers move horizontally and vertically
  static const std::vector<std::pair<int, int>> DIRECTIONS = {
      {0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

  std::vector<Position> moves;

  // Iterate on each direction from origin stepping towards the direction
  // till we found a piece
  for (auto [rowDelta, colDelta] : DIRECTIONS) {
    // Compute adjacent tile in the current direction
    int stepCount = 1;
    Position pos = Position(origin.getX() + rowDelta * stepCount,
                            origin.getY() + colDelta * stepCount);

    // Go on that direction as far as we can
    while (board->isValidPosition(pos) && board->getTile(pos)->isEmpty()) {
      moves.push_back(pos);

      ++stepCount;

      pos = Position(origin.getX() + rowDelta * stepCount,
                     origin.getY() + colDelta * stepCount);
    }

    // If we reach an enemy piece, include its position too
    if (board->isValidPosition(pos) && !board->getTile(pos)->isEmpty() &&
        board->getTile(pos)->getPiece()->getColor() != m_color) {
      moves.push_back(pos);
    }
  }

  return moves;
}
