#include "Gui.h"

#include "SDL.h"

#include <iostream>

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

Gui::Gui(std::function<void(Position)> const &tileClickCb,
         std::function<void()> const &exitCb) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    throw std::runtime_error("Error initialising SDL2");
  }

  m_render = std::make_unique<GuiRenderer>();

  auto rawClickCb = [this, tileClickCb](int x, int y) {
    // X & Y coordinated are in screen domain, they must be mapped
    // to a tile
    auto [clickX, clickY] =
        screenToWindowCoordinates(m_render->getBoardWindow(), x, y);
    auto [tileCol, tileRow] = windowCoordinateToTile(
        m_render->getBoardWindow(), m_render->getTileSize(),
        m_render->getOffsetX(), m_render->getOffsetY(), clickX, clickY);
    if (tileRow >= 0 && tileCol >= 0) {
      tileClickCb(Position(tileRow, tileCol));
    }
  };

  m_input = std::make_unique<GuiInput>(rawClickCb, exitCb);
}

void Gui::setBoard(ChessBoard *board) {}

void Gui::startInputCapture() {}
