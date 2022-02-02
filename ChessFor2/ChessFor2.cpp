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

  // Just clear any previous possible movements
  if (m_board->isValidPosition(m_lastSelectedTile)) {
    Tile *prevSelectedTile = m_board->getTile(m_lastSelectedTile);
    auto prevCandidateMoves = prevSelectedTile->getPiece()->getMoves(
        m_board.get(), m_lastSelectedTile);
    for (auto &&p : prevCandidateMoves) {
      m_board->getTile(p)->setStatus(TileStatus::NONE);
    }
  }

  // Update the candidate movements
  Tile *selectedTile = m_board->getTile(newSelectedPosition);
  auto candidateMoves =
      selectedTile->getPiece()->getMoves(m_board.get(), newSelectedPosition);
  for (auto &&p : candidateMoves) {
    auto const isEmpty = m_board->getTile(p)->isEmpty();
    m_board->getTile(p)->setStatus(isEmpty ? TileStatus::MOVE_CANDIDATE
                                           : TileStatus::KILL_CANDIDATE);
  }

  m_lastSelectedTile = newSelectedPosition;
}

void ChessFor2::changePlayerTurn() {
  m_lastSelectedTile = Position(-1, -1);
  m_currentPlayer = m_currentPlayer == PieceColor::WHITE ? PieceColor::BLACK
                                                         : PieceColor::WHITE;
}
