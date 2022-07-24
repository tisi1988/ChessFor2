#include "LocalGui.h"

#include "GuiInputHelper.h"
#include "GuiRenderHelper.h"

#include "../ChessFor2.h"

#include <stdexcept>

extern "C" {
#include <SDL.h>
}

namespace {
std::pair<int, int> screenToWindowCoordinates(SDL_Window *boardWindow, int x,
                                              int y) {
  int windowX, windowY;
  SDL_GetWindowPosition(boardWindow, &windowX, &windowY);
  return {x - windowX, y - windowY};
}

std::pair<int, int> windowCoordinateToTile(SDL_Window *boardWindow,
                                           int tileSize, int offsetX,
                                           int offsetY, int x, int y) {
  int windowW, windowH;
  SDL_GetWindowSize(boardWindow, &windowW, &windowH);

  if (x < offsetX || x > (offsetX + tileSize * 8)) {
    return {-1, -1};
  }

  if (y < offsetY || y > (offsetY + tileSize * 8)) {
    return {-1, -1};
  }

  return {(x - offsetX) / tileSize, (y - offsetY) / tileSize};
}
}; // namespace

LocalGui::LocalGui(ChessFor2 *game) : BaseGui(game) {
  m_render = std::make_unique<GuiRenderHelper>(m_window, m_renderer, game);

  auto rawClickCb = [this, game](int x, int y) {
    // X & Y coordinates are in screen domain, they must be mapped
    // to a tile before calling back
    auto [clickX, clickY] = screenToWindowCoordinates(m_window, x, y);
    auto [tileCol, tileRow] = windowCoordinateToTile(
        m_window, m_render->getTileSize(), m_render->getOffsetX(),
        m_render->getOffsetY(), clickX, clickY);
    if (tileRow >= 0 && tileCol >= 0) {
      game->tileClicked(Position(tileRow, tileCol));
    }
  };

  m_input = std::make_unique<GuiInputHelper>(
      rawClickCb, std::bind(&ChessFor2::exit, m_game));
}

LocalGui::~LocalGui() {
  m_render = nullptr;
  m_input = nullptr;
}
