#pragma once

class ChessFor2;

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief The BaseUserIO class implements the basic user IO.
 */
class BaseGui {
public:
  /**
   * @brief Class constructor.
   * @param game The game instance.
   */
  explicit BaseGui(ChessFor2 *game);

  virtual ~BaseGui();

protected:
  ChessFor2 *m_game;

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};
};
