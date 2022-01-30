#include "Piece.h"

#include <memory>

Piece::Piece() : m_type(PieceType::NONE), m_color(PieceColor::WHITE) {}

Piece::Piece(PieceType const &type, PieceColor const &color)
    : m_type(std::move(type)), m_color(color) {}

PieceType Piece::getType() const { return m_type; }
PieceColor Piece::getColor() const { return m_color; }
