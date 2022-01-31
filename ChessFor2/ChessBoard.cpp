#include "ChessBoard.h"

#include "pieces/Pawn.h"
#include "pieces/Piece.h"

#include <tuple>
#include <vector>

ChessBoard::ChessBoard() { initializePieces(); }

Tile *ChessBoard::getTile(Position const &pos) {
  if (!pos.inRange(0, BOARD_SIZE_TILES - 1)) {
    throw std::runtime_error("Invalid coordinate getting a Tile: " +
                             pos.toString());
  }

  std::lock_guard<std::mutex> l(m_tilesMutex);
  return &m_tiles[pos.getX()][pos.getY()];
}

void ChessBoard::initializePieces() {

  static auto const PIECE_ORDER = std::vector<PieceType>{
      PieceType::TOWER, PieceType::HORSE,  PieceType::BISHOP, PieceType::QUEEN,
      PieceType::KING,  PieceType::BISHOP, PieceType::HORSE,  PieceType::TOWER};

  for (int col = 0; col < 8; col++) {
    m_tiles[0][col] =
        Tile(Piece::create(PIECE_ORDER.at(col), PieceColor::BLACK));
    m_tiles[Piece::BLACK_PAWN_INIT_ROW][col] =
        Tile(new Pawn(PieceColor::BLACK));

    m_tiles[Piece::WHITE_PAWN_INIT_ROW][col] =
        Tile(new Pawn(PieceColor::WHITE));
    m_tiles[7][col] =
        Tile(Piece::create(PIECE_ORDER.at(col), PieceColor::WHITE));
  }
}
