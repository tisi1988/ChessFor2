#include "LinearMovingPiece.h"

#include "../ChessBoard.h"

LinearMovingPiece::LinearMovingPiece(PieceColor const &color) : Piece(color) {}

std::vector<Position>
LinearMovingPiece::getMoves(std::vector<std::pair<int, int>> const &directions,
                            ChessBoard *board, Position const &origin,
                            int maxSteps) const {
  std::vector<Position> moves;

  // Iterate on each direction from origin stepping towards the direction
  // till we found a piece
  for (auto [rowDelta, colDelta] : directions) {
    // Compute adjacent tile in the current direction
    int stepCount = 1;
    Position pos = Position(origin.getX() + rowDelta * stepCount,
                            origin.getY() + colDelta * stepCount);

    // Go on that direction as far as we can
    while (stepCount <= maxSteps && board->isValidPosition(pos) &&
           board->getTile(pos)->isEmpty()) {
      moves.push_back(pos);

      ++stepCount;

      pos = Position(origin.getX() + rowDelta * stepCount,
                     origin.getY() + colDelta * stepCount);
    }

    // If we stopped because we found an enemy, include its Position too
    if (stepCount <= maxSteps && board->isValidPosition(pos) &&
        !board->getTile(pos)->isEmpty() &&
        board->getTile(pos)->getPiece()->getColor() != m_color) {
      moves.push_back(pos);
    }
  }

  return moves;
}
