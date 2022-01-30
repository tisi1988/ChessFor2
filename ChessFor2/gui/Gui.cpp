#include "Gui.h"

#include "GuiInputHelper.h"
#include "GuiRenderHelper.h"

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

SDL_Window *createWindow() {
  static constexpr int DEFAULT_WIDTH{600};
  static constexpr int DEFAULT_HEIGHT{600};
  static constexpr char const *WINDOW_TITLE{"ChessFor2"};

  auto window = SDL_CreateWindow(
      WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  if (!window) {
    throw std::runtime_error("Could not create the window");
  }

  return window;
}

SDL_Renderer *createRenderer(SDL_Window *w) {
  auto sdlRenderer = SDL_CreateRenderer(
      w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!sdlRenderer) {
    throw std::runtime_error("Could not create the renderer");
  }

  return sdlRenderer;
}
}; // namespace

Gui::Gui(std::function<void(Position)> const &tileClickCb,
         std::function<void()> const &exitCb) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    throw std::runtime_error("Error initialising SDL2");
  }

  /*
   * NOTE: SDL is supposed to be consumed single-threaded!
   *
   * However, keeping the SDL initialization in the same thread
   * that creates the Window and the Renderer makes it work.
   *
   * The event handling and drawing loops can then be run in
   * separate threads.
   */
  m_window = createWindow();
  m_renderer = createRenderer(m_window);

  m_render = std::make_unique<GuiRenderHelper>(m_window, m_renderer);

  auto rawClickCb = [this, tileClickCb](int x, int y) {
    // X & Y coordinates are in screen domain, they must be mapped
    // to a tile before calling back
    auto [clickX, clickY] = screenToWindowCoordinates(m_window, x, y);
    auto [tileCol, tileRow] = windowCoordinateToTile(
        m_window, m_render->getTileSize(), m_render->getOffsetX(),
        m_render->getOffsetY(), clickX, clickY);
    if (tileRow >= 0 && tileCol >= 0) {
      tileClickCb(Position(tileRow, tileCol));
    }
  };

  m_input = std::make_unique<GuiInputHelper>(rawClickCb, exitCb);
}

Gui::~Gui() {
  m_render = nullptr;
  m_input = nullptr;

  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Gui::setBoard(ChessBoard *board) { m_render->setBoard(board); }
