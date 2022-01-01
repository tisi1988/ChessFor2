#pragma once

extern "C" {
#include <SDL_render.h>
#include <SDL_video.h>
}

#include <atomic>
#include <mutex>
#include <thread>

class ChessBoard;

class GuiRenderer {
public:
  GuiRenderer(SDL_Window *window, SDL_Renderer *sdlRenderer);
  ~GuiRenderer();

  int getOffsetX() const;
  int getOffsetY() const;
  int getTileSize() const;

  void setBoard(ChessBoard *board);

private:
  int getTileSideLength() const;
  std::pair<int, int> getDrawingOffsets() const;
  void drawChessBoard();
  void updateDimensions();

  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_sdlRenderer{nullptr};

  ChessBoard *m_board{nullptr};
  std::mutex m_boardMutex;

  std::atomic_bool m_running{true};
  std::thread m_renderThread;

  int m_windowW{0};
  int m_windowH{0};
  int m_tileSize{0};
  int m_offsetX{0};
  int m_offsetY{0};
};
