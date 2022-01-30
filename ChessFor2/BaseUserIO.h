#pragma once

class ChessFor2;

/**
 * @brief The BaseUserIO class implements the basic user IO.
 */
class BaseUserIO {
public:
  /**
   * @brief Class constructor.
   * @param game The game instance.
   */
  explicit BaseUserIO(ChessFor2 *game) : m_game(game) {}
  virtual ~BaseUserIO() {}

protected:
  ChessFor2 *m_game;
};
