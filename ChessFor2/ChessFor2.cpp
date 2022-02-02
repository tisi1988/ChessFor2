#include "ChessFor2.h"

#include "TileStatus.h"
#include "gui/Gui.h"
#include "pieces/Piece.h"

#include <functional>
#include <iostream>
#include <thread>

ChessFor2::ChessFor2() : m_lastSelectedTile(-1, -1) {
  try {
    m_board = std::make_unique<ChessBoard>();

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

void ChessFor2::tileClicked(Position const &p) {
  std::cout << "Tile Row=" << p.getY() << " Col=" << p.getX() << std::endl;

  // Check if the position is valid
  if (!m_board->isValidPosition(p)) {
    return;
  }

  Tile *clickedTile = m_board->getTile(p);
  if (clickedTile->isEmpty()) {
    // TODO Check if the clicked tile belong to previously computed candidate
    // movements (if any)
  } else if (clickedTile->getPiece()->getColor() == m_currentPlayer) {
    updateMovingPiece(p);
  } else {
    // TODO Check if the clicked tile belong to previously computed candidate
    // and kill the enemy piece

    changePlayerTurn();
  }
}

void ChessFor2::run() {
  std::unique_lock<std::mutex> lk(m_exitMutex);
  m_exitCv.wait(lk, [&running = m_running] { return !running; });
}

void ChessFor2::updateMovingPiece(Position const &newSelectedPosition) {
  if (newSelectedPosition == m_lastSelectedTile) {
    return;
  }

  if (m_board->isValidPosition(m_lastSelectedTile)) {
    clearSelectedPiece();
  }

  setSelectedPiece(newSelectedPosition);
}

void ChessFor2::changePlayerTurn() {
  m_lastSelectedTile = Position(-1, -1);
  m_currentPlayer = m_currentPlayer == PieceColor::WHITE ? PieceColor::BLACK
                                                         : PieceColor::WHITE;
}

void ChessFor2::clearSelectedPiece() {
  Tile *prevSelectedTile = m_board->getTile(m_lastSelectedTile);
  prevSelectedTile->setStatus(TileStatus::NONE);
  auto prevCandidateMoves =
      prevSelectedTile->getPiece()->getMoves(m_board.get(), m_lastSelectedTile);
  for (auto &&p : prevCandidateMoves) {
    m_board->getTile(p)->setStatus(TileStatus::NONE);
  }

  m_lastSelectedTile = Position(-1, -1);
}

void ChessFor2::setSelectedPiece(Position const &pos) {
  Tile *selectedTile = m_board->getTile(pos);

  selectedTile->setStatus(TileStatus::SELECTED);

  auto candidateMoves = selectedTile->getPiece()->getMoves(m_board.get(), pos);
  for (auto &&p : candidateMoves) {
    auto const isEmpty = m_board->getTile(p)->isEmpty();
    m_board->getTile(p)->setStatus(isEmpty ? TileStatus::MOVE_CANDIDATE
                                           : TileStatus::KILL_CANDIDATE);
  }

  m_lastSelectedTile = pos;
}
