#pragma once

#include "GuiInput.h"
#include "GuiRenderer.h"
#include "IUserIO.h"

#include <memory>

class Gui : public IUserIO {
public:
  Gui(const std::function<void(Position)> &tileClickCb,
      const std::function<void()> &exitCb);

  void setBoard(ChessBoard *board) override;
  void startInputCapture() override;

private:
  std::unique_ptr<GuiRenderer> m_render;
  std::unique_ptr<GuiInput> m_input;
};
