#pragma once

#include "pieces/PieceColor.h"

#include <mutex>

/**
 * @brief The GameTurn class contains the information
 * about a game turn.
 */
class GameTurn {
public:
  GameTurn();
  ~GameTurn();

  /**
   * @brief Changes the turn modifying the current player.
   */
  void changeTurn();

  /**
   * @return the current player.
   */
  PieceColor getCurrentPlayer() const;

private:
  mutable std::mutex m_playerMutex;
  PieceColor m_currentPlayer{PieceColor::WHITE};
};
