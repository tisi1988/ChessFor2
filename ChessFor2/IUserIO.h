#pragma once

class ChessBoard;

/**
 * @brief The IUserIO class defines the methods the
 * UI should implement.
 */
class IUserIO {
public:
  virtual ~IUserIO() {}

  /**
   * @brief Set a nerw board data to be displayed.
   * @param board The new chessboard data.
   */
  virtual void setBoard(ChessBoard *board) = 0;
};
