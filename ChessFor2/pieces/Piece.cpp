#include "Piece.h"

#include "Bishop.h"
#include "Horse.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Tower.h"

#include <algorithm>
#include <memory>
#include <stdexcept>

Piece::Piece(PieceColor const &color) : m_color(color) {}

Piece::~Piece() = default;

PieceColor Piece::getColor() const { return m_color; }

Piece *Piece::create(PieceType type, PieceColor color) {
  switch (type) {
  case PieceType::BISHOP:
    return new Bishop(color);
  case PieceType::HORSE:
    return new Horse(color);
  case PieceType::KING:
    return new King(color);
  case PieceType::PAWN:
    return new Pawn(color);
  case PieceType::QUEEN:
    return new Queen(color);
  case PieceType::TOWER:
    return new Tower(color);
  }

  throw std::runtime_error("Invalid Piece type: " +
                           std::to_string(static_cast<int>(type)));
}
