#pragma once

#include "BaseUserIO.h"
#include "ChessBoard.h"
#include "PlayerId.h"

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>

/**
 * @brief The ChessFor2 class contains the logic
 * of the game. Also is the facade between the UI
 * and the backend.
 */
class ChessFor2 {
public:
  ChessFor2();

  void run();

  void exit();
  void tileClicked(Position const &p);
  Tile getTile(Position const &pos) const;

private:
  std::unique_ptr<BaseUserIO> m_io;
  std::unique_ptr<ChessBoard> m_board;
  PlayerId m_currentPlayer{PlayerId::PLAYER1};

  // Stuff to control game exit
  std::mutex m_exitMutex;
  std::condition_variable m_exitCv;
  std::atomic_bool m_running{true};
};
