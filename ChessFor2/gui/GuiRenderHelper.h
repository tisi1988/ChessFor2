#pragma once

#include "PieceImgLoader.h"

#include <atomic>
#include <thread>

class ChessFor2;

struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief The GuiRenderHelper class implements the game rendering
 * through SDL2 API.
 * The game is renderer at 30 FPS. By this way the window can be
 * resized and the chess will be drawn accordingly to the space
 * available on each frame centering the board inside the window.
 */
class GuiRenderHelper {
public:
  /**
   * @brief GuiRenderHelper constructor.
   * @param window The window to draw to.
   * @param renderer The renderer to use.
   */
  GuiRenderHelper(SDL_Window *window, SDL_Renderer *renderer, ChessFor2 *game);
  ~GuiRenderHelper();

  /**
   * @return The offset amount in the horizontal axis. The amount of pixels
   * from the left border of the window till the left border of the first
   * column of the board.
   */
  int getOffsetX() const;

  /**
   * @return The offset amount in the vertical axis. The amount of pixels
   * from the top border of the window till the top border of the first
   * row of the board.
   */
  int getOffsetY() const;

  /**
   * @return The tile size in pixels, both width and height.
   */
  int getTileSize() const;

private:
  int getTileSideLength() const;
  std::pair<int, int> getDrawingOffsets() const;
  void drawChessBoard();
  void updateDimensions();

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};

  ChessFor2 *m_game{nullptr};

  std::atomic_bool m_running{true};
  std::thread m_renderThread;

  int m_windowW{0};
  int m_windowH{0};
  int m_tileSize{0};
  int m_offsetX{0};
  int m_offsetY{0};

  std::unique_ptr<PieceImgLoader> m_imgLoader;
};
