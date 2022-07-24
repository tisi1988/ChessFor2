#include "BaseGui.h"

#include <stdexcept>

extern "C" {
#include <SDL.h>
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

BaseGui::BaseGui(ChessFor2 *game) : m_game(game) {
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
}

BaseGui::~BaseGui() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
