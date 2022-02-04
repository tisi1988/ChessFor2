#include "GameAnalyzer.h"

#include "Tile.h"

GameAnalyzer::GameAnalyzer(std::weak_ptr<ChessBoard> board) : m_board(board) {}

GameResult GameAnalyzer::isGameOver(PieceColor currentPlayer) const {
  // TODO
  // If the only pieces left are Kings -> DRAW
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

void GameAnalyzer::movePiece(Position const &src, Position const &dst) const {
  Tile *srcTile = m_board.lock()->getTile(src);
  Piece *piece = srcTile->getPiece();
  srcTile->clear();

  Tile *dstTile = m_board.lock()->getTile(dst);
  dstTile->clear();
  dstTile->setPiece(piece);
}
