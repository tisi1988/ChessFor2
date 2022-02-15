#include "GameAnalyzer.h"

#include "Tile.h"
#include "pieces/Piece.h"

namespace {
bool isInInitialTilePawn(int row, PieceColor color) {
  static constexpr int BLACK_PAWN_INIT_ROW{1};
  static constexpr int WHITE_PAWN_INIT_ROW{6};

  return row == BLACK_PAWN_INIT_ROW && color == PieceColor::BLACK ||
         row == WHITE_PAWN_INIT_ROW && color == PieceColor::WHITE;
}

bool isInInitialTileKing(int row, PieceColor color) {
  static constexpr int BLACK_KING_INIT_ROW{0};
  static constexpr int WHITE_KING_INIT_ROW{7};

  return row == BLACK_KING_INIT_ROW && color == PieceColor::BLACK ||
         row == WHITE_KING_INIT_ROW && color == PieceColor::WHITE;
}
} // namespace

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

std::vector<Position> GameAnalyzer::getMoves(Position const &origin) const {
  Tile *selectedTile = m_board.lock()->getTile(origin);

  if (selectedTile->isEmpty()) {
    return {};
  }

  // These moves consider other pieces in the way of the chosen piece
  // that can make the chosen piece not going further
  auto pieceMoves =
      selectedTile->getPiece()->getMoves(m_board.lock().get(), origin);

  // Compute additional movements based on game data (like castling)
  auto const pieceType = selectedTile->getPiece()->getType();
  switch (pieceType) {
  case PieceType::PAWN:
    computeAdditionalMovesPawn(pieceMoves, origin);
    break;
  case PieceType::KING:
    computeAdditionalMovesKing(pieceMoves, origin);
    break;
  case PieceType::BISHOP:
  case PieceType::HORSE:
  case PieceType::QUEEN:
  case PieceType::TOWER:
  default:
    // These don't have any special movement
    break;
  }

  return pieceMoves;
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

void GameAnalyzer::computeAdditionalMovesPawn(std::vector<Position> &pieceMoves,
                                              Position const &origin) const {

  PieceColor color = m_board.lock()->getTile(origin)->getPiece()->getColor();
  int const direction = color == PieceColor::BLACK ? 1 : -1;

  // Pawns can move an extra tile forward if their in the initial tile
  Position const secondTile =
      Position(origin.getX() + 2 * direction, origin.getY());

  if (isInInitialTilePawn(origin.getX(), color) &&
      m_board.lock()->isValidPosition(secondTile) &&
      !m_board.lock()->getTile(secondTile)->getPiece()) {
    pieceMoves.push_back(secondTile);
  }

  // It also can move diagonally front-left if there's an enemy piece there
  Position const fl =
      Position(origin.getX() + 1 * direction, origin.getY() - 1);

  if (isEnemyPieceOnPosition(color, fl)) {
    pieceMoves.push_back(fl);
  }

  // It also can move diagonally front-right if there's an enemy piece there
  Position const fr =
      Position(origin.getX() + 1 * direction, origin.getY() + 1);

  if (isEnemyPieceOnPosition(color, fr)) {
    pieceMoves.push_back(fr);
  }
}

void GameAnalyzer::computeAdditionalMovesKing(std::vector<Position> &pieceMoves,
                                              Position const &origin) const {
  // TODO
}

bool GameAnalyzer::isEnemyPieceOnPosition(PieceColor playing,
                                     Position const &pos) const {
  Tile *tile{nullptr};

  if (m_board.lock()->isValidPosition(pos)) {
    tile = m_board.lock()->getTile(pos);
  }

  return tile && !tile->isEmpty() && tile->getPiece()->getColor() != playing;
}
