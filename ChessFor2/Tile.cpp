#include "Tile.h"

#include "pieces/Piece.h"

#include <memory>

Tile::Tile() {}

Tile::Tile(Piece *piece) : m_piece(piece) {}

Tile::Tile(Tile const &other) : m_piece(other.m_piece) {}

Piece *Tile::getPiece() const { return m_piece; }

void Tile::setPiece(Piece *piece) { m_piece = piece; }

bool Tile::isEmpty() const { return !m_piece; }

TileStatus Tile::getStatus() const { return m_status; }

void Tile::setStatus(TileStatus status) { m_status = status; }

Tile &Tile::operator=(Tile const &other) {
  m_piece = other.m_piece;
  return *this;
}
