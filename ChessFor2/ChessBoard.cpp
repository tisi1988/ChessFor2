#include "ChessBoard.h"

#include <tuple>
#include <vector>

ChessBoard::ChessBoard() { initializePieces(); }

Tile ChessBoard::getTile(Position const &pos) const {
  return Tile(m_tiles[pos.getX()][pos.getY()]);
}

void ChessBoard::initializePieces() {
  static auto const pieceOrder = std::vector<PieceType>{
      PieceType::TOWER, PieceType::HORSE,  PieceType::BISHOP, PieceType::QUEEN,
      PieceType::KING,  PieceType::BISHOP, PieceType::HORSE,  PieceType::TOWER};

  for (auto &row : {0, 1}) {
    for (int col = 0; col < 8; col++) {
      m_tiles[row][col] = Tile(Piece(
          row == 0 ? pieceOrder[col] : PieceType::PAWN, PieceColor::BLACK));
      m_tiles[7 - row][col] = Tile(Piece(
          row == 0 ? pieceOrder[col] : PieceType::PAWN, PieceColor::WHITE));
    }
  }
}
