#include "GuiRenderer.h"

#include "ChessBoard.h"

extern "C" {
#include <SDL_render.h>
}

#include <stdexcept>

GuiRenderer::GuiRenderer()
{
    static constexpr int DEFAULT_WIDTH = 600;
    static constexpr int DEFAULT_HEIGHT = 600;

    m_window = SDL_CreateWindow("ChessFor2", // Title
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Position
            DEFAULT_WIDTH, DEFAULT_HEIGHT,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if (!m_window) {
        throw std::runtime_error("Could not create the window");
    }

    m_renderThread = std::thread(&GuiRenderer::drawChessBoard, this);
}

GuiRenderer::~GuiRenderer() {
    m_running = false;
    m_renderThread.join();
}

SDL_Window* GuiRenderer::getBoardWindow() const {
    return m_window;
}

void GuiRenderer::setBoard(ChessBoard* board) {
    std::lock_guard<std::mutex> l(m_boardMutex);
    m_board = board;
}

void clearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
}

void setTileColor(SDL_Renderer* renderer, int row, int col) {
    // 0 for dark tile, 1 for light tile
    int tileColor = 1;
    if((row % 2 == 0 && col % 2 == 0) || (row % 2 != 0 && col % 2 != 0)) {
        tileColor = 0;
    }

    if(tileColor == 0) {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    }
}

std::pair<int, int> GuiRenderer::getTileDimensions() const {
    int windowW, windowH;
    SDL_GetWindowSize(m_window, &windowW, &windowH);

    return {windowW / 8, windowH / 8};
}

void drawBackgorund(SDL_Renderer* renderer, int tileW, int tileH) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            setTileColor(renderer, row, col);
            // Create the cell rectangle
            SDL_Rect cell_rect;
            cell_rect.x = col * tileW;
            cell_rect.y = row * tileH;
            cell_rect.w = tileW;
            cell_rect.h = tileH;

            // Render our cell through SDL_Rect
            SDL_RenderFillRect(renderer, &cell_rect);
        }
    }
}

void GuiRenderer::drawChessBoard() {
    auto constexpr FPS{30};

    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    auto sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    while(m_running) {
        clearScreen(sdlRenderer);
        auto [tileW, tileH] = getTileDimensions();
        drawBackgorund(sdlRenderer, tileW, tileH);

        {
            std::lock_guard<std::mutex> l(m_boardMutex);
            // TODO Draw pieces
        }

        // Update the screen
        SDL_RenderPresent(sdlRenderer);

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds{1000 / FPS});
    }
}
