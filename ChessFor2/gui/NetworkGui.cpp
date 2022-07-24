#include "NetworkGui.h"

#include "../net/NetworkIoHelper.h"
#include "GuiInputHelper.h"
#include "GuiRenderHelper.h"
#include "NetworkGui.h"

#include "../ChessFor2.h"

#include <functional>
#include <stdexcept>

extern "C" {
#include <SDL.h>
}

namespace {
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

NetworkGui::NetworkGui(ChessFor2 *game) : BaseGui(game) {
  m_render = std::make_unique<GuiRenderHelper>(m_window, m_renderer, game);

  m_input = std::make_unique<GuiInputHelper>(
      [](int, int) {}, std::bind(&ChessFor2::exit, m_game));

  m_networkIo = std::make_unique<NetworkIoHelper>(
      [game](int tileRow, int tileCol) {
        game->tileClicked(Position(tileRow, tileCol));
      },
      std::bind(&ChessFor2::exit, m_game));
}

NetworkGui::~NetworkGui() {
  m_render = nullptr;
  m_networkIo = nullptr;
}
