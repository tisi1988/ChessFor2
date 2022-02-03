#include "GameTurn.h"

GameTurn::GameTurn() = default;

GameTurn::~GameTurn() = default;

void GameTurn::changeTurn() {
  std::lock_guard<std::mutex> l(m_playerMutex);
  m_currentPlayer = m_currentPlayer == PieceColor::WHITE ? PieceColor::BLACK
                                                         : PieceColor::WHITE;
}

PieceColor GameTurn::getCurrentPlayer() const {
  std::lock_guard<std::mutex> l(m_playerMutex);
  return m_currentPlayer;
}
