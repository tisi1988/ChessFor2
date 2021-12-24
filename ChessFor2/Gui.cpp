#include "Gui.h"

#include "SDL.h"

#include <iostream>

Gui::Gui() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw std::runtime_error("Error initialising SDL2");
    }

    m_render = std::make_unique<GuiRenderer>();
}

void Gui::displayBoard(ChessBoard const& board) {

}

void Gui::startInputCapture() {

}

void Gui::setClickedPositionCallback(std::function<void (Position)> f)
{
    m_clickPositionCallback = f;
}

void Gui::setGameExitCallback(std::function<void ()> f)
{
    m_gameExitCallback = f;
}
