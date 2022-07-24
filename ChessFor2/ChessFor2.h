#pragma once

#include "ChessBoard.h"
#include "GameAnalyzer.h"
#include "GameTurn.h"
#include "gui/BaseGui.h"

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

/**
 * @brief The ChessFor2 class is the facade between the UI
 * and the backend. It handles the logic regarding the
 * user interaction like selecting a piece to move, or
 * update the Tile status to show the user the possible
 * movements to do with that piece.
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
  Tile *getTile(Position const &pos);

  /**
   * @return the GameTurn instance.
   */
  GameTurn *getGameTurn() const;

private:
  void updateMovingPiece(Position const &p);
  void clearSelectedPiece();
  void setSelectedPiece(Position const &pos);

  std::unique_ptr<BaseGui> m_io;
  std::shared_ptr<ChessBoard> m_board;

  // Game logic stuff
  Position m_selectedPiece;
  std::vector<Position> m_selectedPieceMoves;
  std::unique_ptr<GameTurn> m_gameTurn;
  std::unique_ptr<GameAnalyzer> m_gameAnalyzer;

  // Stuff to control game exit
  std::mutex m_exitMutex;
  std::condition_variable m_exitCv;
  std::atomic_bool m_running{true};
};
