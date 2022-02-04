#include "GameAnalyzer.h"

#include "Tile.h"
#include "pieces/Piece.h"

GameAnalyzer::GameAnalyzer(std::weak_ptr<ChessBoard> board) : m_board(board) {
  initializeRemainingPieces();
}

GameResult GameAnalyzer::isGameOver(PieceColor currentPlayer) const {
  // TODO
  // If draw conditions -> DRAW
  // If the opposite King is under attack -> DEFEAT
  // otherwise -> NONE
  return GameResult::NONE;
}

bool GameAnalyzer::isSuicidalMovement(Position const &src,
                                      Position const &dst) const {
  // TODO
  // Implement this in terms of isGameOver()
  return true;
}

void GameAnalyzer::movePiece(Position const &src, Position const &dst) {
  Tile *srcTile = m_board.lock()->getTile(src);
  Piece *piece = srcTile->getPiece();
  srcTile->clear();

  Tile *dstTile = m_board.lock()->getTile(dst);
  if (!dstTile->isEmpty()) {
    // The piece on destination is 'killed'
    Piece *victim = dstTile->getPiece();
    m_piecesByPlayer[static_cast<int>(victim->getColor())].erase(victim);
    dstTile->clear();
  }

  m_piecesByPlayer[static_cast<int>(piece->getColor())][piece] = dst;

  dstTile->setPiece(piece);
}

void GameAnalyzer::initializeRemainingPieces() {
  // This method is suppoed to be called right after the board is initialized
  // but just in case, let's scan the board instead
  for (int row = 0; row < ChessBoard::BOARD_SIZE_TILES; row++) {
    for (int col = 0; col < ChessBoard::BOARD_SIZE_TILES; col++) {
      Position position(col, row);
      Tile *t = m_board.lock()->getTile(position);
      if (t->isEmpty()) {
        continue;
      }

      Piece *piece = t->getPiece();
      m_piecesByPlayer[static_cast<int>(piece->getColor())][piece] = position;
    }
  }
}
