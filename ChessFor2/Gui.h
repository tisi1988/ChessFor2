#pragma once

#include "GuiInputHelper.h"
#include "GuiRenderHelper.h"
#include "IUserIO.h"

#include <memory>

class Gui : public IUserIO {
public:
  Gui(const std::function<void(Position)> &tileClickCb,
      const std::function<void()> &exitCb);
  ~Gui();

  void setBoard(ChessBoard *board) override;
  void startInputCapture() override;

private:
  std::unique_ptr<GuiRenderHelper> m_render;
  std::unique_ptr<GuiInputHelper> m_input;

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};
};
