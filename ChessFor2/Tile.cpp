#include "Tile.h"

#include <memory>

Tile::Tile() {}

Tile::Tile(Piece const &piece) : m_piece(std::move(piece)) {}

Tile::Tile(Tile const &other) : m_piece(other.m_piece) {}

Piece Tile::getPiece() const { return m_piece; }

void Tile::setPiece(Piece const &piece) { m_piece = piece; }

Tile &Tile::operator =(Tile const &other) {
  m_piece = other.m_piece;
  return *this;
}
