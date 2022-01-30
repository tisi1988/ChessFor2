#pragma once

#include "../PieceColor.h"
#include "../PieceType.h"
#include "../Position.h"

struct SDL_Texture;
struct SDL_Renderer;

/**
 * @brief The PieceImgLoader class implements the
 * chess piece image loading from a file and creates
 * an SDL texture ready to draw. It uses SDL_Image library.
 */
class PieceImgLoader {
public:
  /**
   * @brief Class constructor.
   * @param renderer The renderer to create the texture for displaying.
   */
  explicit PieceImgLoader(SDL_Renderer *renderer);
  ~PieceImgLoader();

  /**
   * @brief Returns the position of a piece sprite inside the image.
   * @param type The type of piece to draw.
   * @param color The color of the piece to draw.
   * @return The position of the requested piece and color sprite inside the
   * image.
   */
  Position getPieceTextureCoordinate(PieceType type, PieceColor color) const;

  /**
   * @return the texture containing all the pieces sprites.
   */
  SDL_Texture *getPiecesTexture() const;

  /**
   * @return width of the sprite of a piece.
   */
  int getPieceWidth() const;

  /**
   * @return height of the sprite of a piece.
   */
  int getPieceHeight() const;

private:
  SDL_Texture *m_texture;

  int m_pieceWidth;
  int m_pieceHeight;
};
