#pragma once

#include "BaseGui.h"

#include <memory>

class ChessFor2;

class GuiRenderHelper;
class GuiInputHelper;

/**
 * @brief The Gui class inherits from BaseUserIO
 * and implements an specific user IO.
 *
 * This implementation uses SDL2 library.
 */
class LocalGui : public BaseGui {
public:
  /**
   * @brief Gui constructor.
   * @param game Game instance.
   */
  LocalGui(ChessFor2 *game);

  ~LocalGui();

private:
  std::unique_ptr<GuiRenderHelper> m_render;
  std::unique_ptr<GuiInputHelper> m_input;
};
