#include "Gui.h"

#include "SDL.h"

#include <iostream>

std::pair<int, int> screenToWindowCoordinates(SDL_Window *boardWindow, int x,
                                              int y) {
  int windowX, windowY;
  SDL_GetWindowPosition(boardWindow, &windowX, &windowY);
  return {x - windowX, y - windowY};
}

std::pair<int, int> windowCoordinateToTile(SDL_Window *boardWindow, int x,
                                           int y) {
  int windowW, windowH;
  SDL_GetWindowSize(boardWindow, &windowW, &windowH);
  // Compute the tile size in pixels
  int const tileWidth = windowW / 8;
  int const tileHeight = windowH / 8;
  return {x / tileWidth, y / tileHeight};
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
    auto [tileCol, tileRow] =
        windowCoordinateToTile(m_render->getBoardWindow(), clickX, clickY);
    tileClickCb(Position(tileRow, tileCol));
  };

  m_input = std::make_unique<GuiInput>(rawClickCb, exitCb);
}

void Gui::setBoard(ChessBoard *board) {}

void Gui::startInputCapture() {}
