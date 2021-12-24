#pragma once

#include <SDL.h>

class GuiRenderer
{
public:
    GuiRenderer();

private:
    SDL_Window* m_window{nullptr};
};
