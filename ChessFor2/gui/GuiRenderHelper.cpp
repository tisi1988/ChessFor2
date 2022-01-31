#include "GuiRenderHelper.h"

#include "../ChessFor2.h"
#include "../pieces/Piece.h"

extern "C" {
#include <SDL_render.h>
}

#include <iostream>
#include <stdexcept>

namespace {
void clearScreen(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);
}

void setDefaultTileColor(SDL_Renderer *renderer, int row, int col) {
  // 0 for dark tile, 1 for light tile
  bool lightColor{true};
  if ((row % 2 == 0 && col % 2 == 0) || (row % 2 != 0 && col % 2 != 0)) {
    lightColor = false;
  }

  if (lightColor) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  } else {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
  }
}

void setTileColor(SDL_Renderer *renderer, TileStatus tileStatus, int row,
                  int col) {
  if (tileStatus == TileStatus::NONE) {
    setDefaultTileColor(renderer, row, col);
  } else if (tileStatus == TileStatus::MOVE_CANDIDATE) {
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, SDL_ALPHA_OPAQUE);
  }
}

void drawBackgorund(SDL_Renderer *renderer, ChessFor2 *game, int offsetX,
                    int offsetY, int tileSide) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      setTileColor(renderer, game->getTile(Position(row, col))->getStatus(),
                   row, col);
      // Create the cell rectangle
      SDL_Rect cell_rect;
      cell_rect.x = col * tileSide + offsetX;
      cell_rect.y = row * tileSide + offsetY;
      cell_rect.w = tileSide;
      cell_rect.h = tileSide;

      // Render our cell through SDL_Rect
      SDL_RenderFillRect(renderer, &cell_rect);
    }
  }
}

void drawPieces(SDL_Renderer *renderer, PieceImgLoader *imgLoader,
                ChessFor2 *game, int offsetX, int offsetY, int tileSide) {
  int const pieceWidth = imgLoader->getPieceWidth();
  int const pieceHeight = imgLoader->getPieceHeight();

  // Whites x=208*i y=0
  // Black  x=208*i y=213
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      Piece *piece;
      try {
        piece = game->getTile(Position(row, col))->getPiece();
      } catch (std::runtime_error const &e) {
        throw;
      }

      if (!piece) {
        continue;
      }

      auto const pieceTextureLoc = imgLoader->getPieceTextureCoordinate(
          piece->getType(), piece->getColor());

      SDL_Rect srcrect = {pieceTextureLoc.getX(), pieceTextureLoc.getY(),
                          pieceWidth, pieceHeight};
      SDL_Rect dstrect = {offsetX + col * tileSide, offsetY + row * tileSide,
                          tileSide, tileSide};

      SDL_RenderCopy(renderer, imgLoader->getPiecesTexture(), &srcrect,
                     &dstrect);
    }
  }
}
}; // namespace

GuiRenderHelper::GuiRenderHelper(SDL_Window *window, SDL_Renderer *renderer,
                                 ChessFor2 *game)
    : m_window(window), m_renderer(renderer), m_game(game),
      m_imgLoader(std::make_unique<PieceImgLoader>(renderer)) {
  m_renderThread = std::thread(&GuiRenderHelper::drawChessBoard, this);
}

GuiRenderHelper::~GuiRenderHelper() {
  m_running = false;
  m_renderThread.join();
}

int GuiRenderHelper::getOffsetX() const { return m_offsetX; }

int GuiRenderHelper::getOffsetY() const { return m_offsetY; }

int GuiRenderHelper::getTileSize() const { return m_tileSize; }

void GuiRenderHelper::updateDimensions() {
  int w, h;
  SDL_GetWindowSize(m_window, &w, &h);

  if (w == m_windowW && h == m_windowH) {
    return;
  }

  m_windowW = w;
  m_windowH = h;

  int const minSize = std::min(m_windowW, m_windowH);

  m_tileSize = minSize / 8;
  m_offsetX = (m_windowW - minSize) / 2;
  m_offsetY = (m_windowH - minSize) / 2;
}

void GuiRenderHelper::drawChessBoard() {
  auto constexpr FPS{30};

  try {
    while (m_running) {
      clearScreen(m_renderer);
      updateDimensions();
      drawBackgorund(m_renderer, m_game, m_offsetX, m_offsetY, m_tileSize);

      drawPieces(m_renderer, m_imgLoader.get(), m_game, m_offsetX, m_offsetY,
                 m_tileSize);

      // Update the screen
      SDL_RenderPresent(m_renderer);

      // Sleep
      std::this_thread::sleep_for(std::chrono::milliseconds{1000 / FPS});
    }
  } catch (std::runtime_error const &e) {
    std::cout << std::string("Error while drawing ") + e.what();
  } catch (...) {
    std::cout << "Unknown error while drawing";
  }
}
