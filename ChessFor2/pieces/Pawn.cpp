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

  addFrontMoves(dest, board, origin);
  addKills(dest, board, origin);

  return dest;
}

void Pawn::addFrontMoves(std::vector<Position> &moves, ChessBoard *board,
                         Position const &origin) const {
  try {
    Position const frontTile =
        Position(origin.getX() + 1 * m_direction, origin.getY());

    // If there's no piece on that position, it can move there
    if (board->isValid(frontTile) && !board->getTile(frontTile)->getPiece()) {
      moves.push_back(frontTile);

      // Pawns can move an extra tile forward if their in the initial tile
      Position const secondTile =
          Position(frontTile.getX() + 1 * m_direction, frontTile.getY());
      if (isInInitialTile(origin.getX(), m_color) &&
          board->isValid(secondTile) &&
          !board->getTile(secondTile)->getPiece()) {
        moves.push_back(secondTile);
      }
    }
  } catch (std::runtime_error const &e) {
    throw std::runtime_error("Error trying to check front moves for Pawn at " +
                             origin.toString() + ": " + e.what());
  }
}

void Pawn::addKills(std::vector<Position> &moves, ChessBoard *board,
                    Position const &origin) const {

  try {
    // It also can move diagonally front-left if there's an enemy piece there
    Position const fl =
        Position(origin.getX() + 1 * m_direction, origin.getY() - 1);

    if (checkPossibleKill(board, fl)) {
      moves.push_back(fl);
    }

    // It also can move diagonally front-right if there's an enemy piece there
    Position const fr =
        Position(origin.getX() + 1 * m_direction, origin.getY() + 1);

    if (checkPossibleKill(board, fr)) {
      moves.push_back(fr);
    }
  } catch (std::runtime_error const &) {
    // We end up in an invalid position
    // either in the left or the right forward
  }
}

bool Pawn::checkPossibleKill(ChessBoard *board, Position const &pos) const {
  Tile *tile{nullptr};

  if (board->isValid(pos)) {
    tile = board->getTile(pos);
  }

  return tile && !tile->isEmpty() && tile->getPiece()->getColor() != m_color;
}
