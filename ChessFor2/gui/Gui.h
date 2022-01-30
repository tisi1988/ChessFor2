#pragma once

#include "../BaseUserIO.h"

#include <memory>

class ChessFor2;

class GuiRenderHelper;
class GuiInputHelper;

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief The Gui class inherits from BaseUserIO
 * and implements an specific user IO.
 *
 * This implementation uses SDL2 library.
 */
class Gui : public BaseUserIO {
public:
  /**
   * @brief Gui constructor.
   * @param game Game instance.
   */
  Gui(ChessFor2 *game);

  ~Gui();

private:
  std::unique_ptr<GuiRenderHelper> m_render;
  std::unique_ptr<GuiInputHelper> m_input;

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};
};
