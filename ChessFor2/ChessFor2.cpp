#include "ChessFor2.h"

#include "TileStatus.h"
#include "gui/Gui.h"
#include "pieces/Piece.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>

namespace {
template <typename T> bool contains(std::vector<T> c, T const &v) {
  return std::find_if(c.begin(), c.end(),
                      [&v](T const &p) { return p == v; }) != c.end();
}
} // namespace

ChessFor2::ChessFor2() : m_selectedPiece(-1, -1) {
  try {
    m_board = std::make_unique<ChessBoard>();
    m_gameTurn = std::make_unique<GameTurn>();

    // Create I/O at the end when the backend is ready
    m_io = std::make_unique<Gui>(this);
  } catch (std::runtime_error const &e) {
    std::cout << "Error initializing: " << e.what() << std::endl;
  }
}

void ChessFor2::exit() {
  m_running = false;
  m_exitCv.notify_one();
}

Tile *ChessFor2::getTile(Position const &pos) {
  return m_board->getTile(std::move(pos));
}

GameTurn *ChessFor2::getGameTurn() const { return m_gameTurn.get(); }

void ChessFor2::tileClicked(Position const &p) {
  // Check if the position is valid
  if (!m_board->isValidPosition(p)) {
    return;
  }

  Tile *clickedTile = m_board->getTile(p);
  if (contains(m_selectedPieceMoves, p)) {
    // The clicked tile belong to a candidate movements
    moveSelectedPiece(p);
    changePlayerTurn();
  } else if (!clickedTile->isEmpty() && clickedTile->getPiece()->getColor() ==
                                            m_gameTurn->getCurrentPlayer()) {
    updateMovingPiece(p);
  }
}

void ChessFor2::run() {
  std::unique_lock<std::mutex> lk(m_exitMutex);
  m_exitCv.wait(lk, [&running = m_running] { return !running; });
}

void ChessFor2::updateMovingPiece(Position const &newSelectedPosition) {
  if (newSelectedPosition == m_selectedPiece) {
    return;
  }

  if (m_board->isValidPosition(m_selectedPiece)) {
    clearSelectedPiece();
  }

  setSelectedPiece(newSelectedPosition);
}

void ChessFor2::changePlayerTurn() {
  m_selectedPiece = Position(-1, -1);
  m_gameTurn->changeTurn();
}

void ChessFor2::clearSelectedPiece() {
  Tile *prevSelectedTile = m_board->getTile(m_selectedPiece);
  prevSelectedTile->setStatus(TileStatus::NONE);
  auto prevCandidateMoves =
      prevSelectedTile->getPiece()->getMoves(m_board.get(), m_selectedPiece);
  for (auto &&p : prevCandidateMoves) {
    m_board->getTile(p)->setStatus(TileStatus::NONE);
  }

  m_selectedPiece = Position(-1, -1);
  m_selectedPieceMoves.clear();
}

void ChessFor2::setSelectedPiece(Position const &pos) {
  m_selectedPiece = pos;

  Tile *selectedTile = m_board->getTile(m_selectedPiece);

  selectedTile->setStatus(TileStatus::SELECTED);

  m_selectedPieceMoves =
      selectedTile->getPiece()->getMoves(m_board.get(), m_selectedPiece);
  for (auto &&p : m_selectedPieceMoves) {
    auto const isEmpty = m_board->getTile(p)->isEmpty();
    m_board->getTile(p)->setStatus(isEmpty ? TileStatus::MOVE_CANDIDATE
                                           : TileStatus::KILL_CANDIDATE);
  }
}

void ChessFor2::moveSelectedPiece(Position const &p) {
  auto const src = m_selectedPiece;

  clearSelectedPiece();

  Tile *srcTile = m_board->getTile(src);
  Piece *piece = srcTile->getPiece();
  srcTile->clear();

  Tile *dstTile = m_board->getTile(p);
  dstTile->clear();
  dstTile->setPiece(piece);
}
