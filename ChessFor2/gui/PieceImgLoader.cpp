#include "PieceImgLoader.h"

extern "C" {
#include <SDL_image.h>
}

PieceImgLoader::PieceImgLoader(SDL_Renderer *renderer) {
  SDL_Surface *pieces_image = IMG_Load("pieces.png");

  // Piece layout: 2x6. Whites first row and blacks in the second
  m_pieceWidth = pieces_image->w / 6;
  m_pieceHeight = pieces_image->h / 2;

  m_texture = SDL_CreateTextureFromSurface(renderer, pieces_image);
}

PieceImgLoader::~PieceImgLoader() { SDL_DestroyTexture(m_texture); }

Position PieceImgLoader::getPieceTextureCoordinate(PieceType type,
                                                   PieceColor color) const {
  // Whites x=208*i y=0
  // Black  x=208*i y=213

  int const offsetY = color == PieceColor::WHITE ? 0 : 213;
  int offsetX_miltiplier;

  switch (type) {
  case PieceType::QUEEN:
    offsetX_miltiplier = 1;
    break;
  case PieceType::BISHOP:
    offsetX_miltiplier = 2;
    break;
  case PieceType::HORSE:
    offsetX_miltiplier = 3;
    break;
  case PieceType::TOWER:
    offsetX_miltiplier = 4;
    break;
  case PieceType::PAWN:
    offsetX_miltiplier = 5;
    break;
  case PieceType::KING:
    [[fallthrough]];
  case PieceType::NONE:
    [[fallthrough]];
  default:
    offsetX_miltiplier = 0;
    break;
  }

  return {offsetX_miltiplier * 208 + 20, offsetY};
}

SDL_Texture *PieceImgLoader::getPiecesTexture() const { return m_texture; }

int PieceImgLoader::getPieceWidth() const { return m_pieceWidth; }

int PieceImgLoader::getPieceHeight() const { return m_pieceHeight; }
