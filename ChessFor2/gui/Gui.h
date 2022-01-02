#pragma once

#include "../IUserIO.h"
#include "../Position.h"

#include <functional>
#include <memory>

class GuiRenderHelper;
class GuiInputHelper;

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief The Gui class implements the UserIO
 * methods based on a Graphic User Interface.
 *
 * This implementation uses SDL2 library.
 */
class Gui : public IUserIO {
public:
  /**
   * @brief Gui constructor.
   * @param tileClickCb Callback for tile click.
   * @param exitCb Callback for game exit.
   */
  Gui(const std::function<void(Position)> &tileClickCb,
      const std::function<void()> &exitCb);

  ~Gui();

  void setBoard(ChessBoard *board) override;

private:
  std::unique_ptr<GuiRenderHelper> m_render;
  std::unique_ptr<GuiInputHelper> m_input;

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};
};
