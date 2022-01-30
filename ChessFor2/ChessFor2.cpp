#include "ChessFor2.h"
#include "gui/Gui.h"

#include <iostream>
#include <thread>

ChessFor2::ChessFor2() {
  try {
    m_io = std::make_unique<Gui>(
        [](Position const &p) {
          std::cout << "Tile Row=" << p.getX() << " Col=" << p.getY()
                    << std::endl;
        },
        [&flag = m_running]() { flag = false; });
    m_board = std::make_unique<ChessBoard>();

    m_io->setBoard(m_board.get());
  } catch (std::runtime_error const &e) {
    std::cout << "Error initializing: " << e.what() << std::endl;
  }
}

void ChessFor2::run() {
  while (m_running) {
    std::this_thread::sleep_for(std::chrono::seconds{1});
  }
}
