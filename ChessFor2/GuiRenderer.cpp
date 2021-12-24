#include "GuiRenderer.h"

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
}
