#pragma once

#include "BaseUserIO.h"
#include "ChessBoard.h"
#include "PlayerId.h"

#include <atomic>
#include <memory>

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

  std::atomic_bool m_running{true};
};
