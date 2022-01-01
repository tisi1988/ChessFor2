#pragma once

#include "ChessBoard.h"
#include "IUserIO.h"
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

  void positionClicked();
  void exitGame();

private:
  std::unique_ptr<IUserIO> m_io;
  std::unique_ptr<ChessBoard> m_board;
  PlayerId m_currentPlayer{PlayerId::PLAYER1};

  std::atomic_bool m_running{true};
};
