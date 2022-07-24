#pragma once

#include "BaseGui.h"

#include <memory>

class ChessFor2;

class GuiRenderHelper;
class GuiInputHelper;
class NetworkIoHelper;

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief The Gui class inherits from BaseUserIO
 * and implements an specific user IO.
 */
class NetworkGui : public BaseGui {
public:
  /**
   * @brief Gui constructor.
   * @param game Game instance.
   */
  NetworkGui(ChessFor2 *game);

  ~NetworkGui();

private:
  std::unique_ptr<GuiRenderHelper> m_render;
  std::unique_ptr<GuiInputHelper> m_input;
  std::unique_ptr<NetworkIoHelper> m_networkIo;
};
