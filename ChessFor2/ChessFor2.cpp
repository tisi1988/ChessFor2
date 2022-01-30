#include "ChessFor2.h"
#include "gui/Gui.h"

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

void ChessFor2::exit() { m_running = false; }

Tile ChessFor2::getTile(Position const &pos) const {
  return m_board->getTile(std::move(pos));
}

void ChessFor2::tileClicked(Position const &p) {
  std::cout << "Tile Row=" << p.getX() << " Col=" << p.getY() << std::endl;
}

void ChessFor2::run() {
  while (m_running) {
    std::this_thread::sleep_for(std::chrono::seconds{1});
  }
}
