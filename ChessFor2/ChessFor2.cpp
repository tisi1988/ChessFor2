#include "ChessFor2.h"

#include "TileStatus.h"
#include "gui/Gui.h"
#include "pieces/Piece.h"

#include <functional>
#include <iostream>
#include <thread>

ChessFor2::ChessFor2() {
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

  // Check if the clicked tile contains a piece of the current player
  Tile *clickedTile{nullptr};
  try {
    clickedTile = m_board->getTile(p);
  } catch (std::runtime_error const &e) {
    std::cout << std::string("Error getting the tile clicked: ") + e.what();

    return;
  }

  Piece *clickedPiece = clickedTile->getPiece();

  if (!clickedPiece || clickedPiece->getColor() != m_currentPlayer) {
    // Clicked empty Tile or opponent's piece, do nothing
    return;
  }

  // The clicked Tile contains a piece of the current player get possible moves
  auto candidateMoves = clickedPiece->getMoves(m_board.get(), p);

  // Set all the possible destinations
  for (auto &&p : candidateMoves) {
    m_board->getTile(p)->setStatus(TileStatus::MOVE_CANDIDATE);
  }
}

void ChessFor2::run() {
  std::unique_lock<std::mutex> lk(m_exitMutex);
  m_exitCv.wait(lk, [&running = m_running] { return !running; });
}
