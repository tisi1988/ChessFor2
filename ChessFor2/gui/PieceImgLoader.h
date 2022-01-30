#pragma once

#include "../PieceColor.h"
#include "../PieceType.h"
#include "../Position.h"

struct SDL_Texture;
struct SDL_Renderer;

class PieceImgLoader {
public:
  explicit PieceImgLoader(SDL_Renderer *renderer);
  ~PieceImgLoader();

  Position getPieceTextureCoordinate(PieceType type, PieceColor color) const;
  SDL_Texture *getPiecesTexture() const;

  int getPieceWidth() const;
  int getPieceHeight() const;

private:
  SDL_Texture *m_texture;

  int m_pieceWidth;
  int m_pieceHeight;
};
