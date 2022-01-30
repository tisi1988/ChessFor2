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
  /**
   * @brief ChessFor2 class constructor.
   */
  ChessFor2();

  /**
   * @brief It runs the game. This call is blocking
   * till the game exits.
   */
  void run();

  /**
   * @brief Triggers the game exit and unlocks run() caller.
   */
  void exit();

  /**
   * @brief Notifies a Tile that's has been clicked.
   * @param p Position of the Tile clicked.
   */
  void tileClicked(Position const &p);

  /**
   * @brief Retusn a Tile fro a given position.
   * @param pos The position of the requested Tile.
   * @return the Tile on the given position.
   */
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
