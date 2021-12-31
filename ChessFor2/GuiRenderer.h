#pragma once

extern "C" {
#include <SDL_video.h>
}

#include <atomic>
#include <thread>
#include <mutex>

class ChessBoard;

class GuiRenderer
{
public:
    GuiRenderer();
    ~GuiRenderer();

    SDL_Window* getBoardWindow() const;

    void setBoard(ChessBoard* board);

private:
    std::pair<int, int> getTileDimensions() const;
    void drawChessBoard();

    SDL_Window* m_window{nullptr};

    ChessBoard* m_board{nullptr};
    std::mutex m_boardMutex;

    std::atomic_bool m_running{true};
    std::thread m_renderThread;
};
