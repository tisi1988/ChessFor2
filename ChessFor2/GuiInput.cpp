#include "GuiInput.h"

extern "C" {
#include <SDL_events.h>
}

#include <iostream>

GuiInput::GuiInput(std::function<void (int, int)> clickCb, std::function<void ()> exitCb)
    : m_clickPositionCallback(clickCb),
    m_gameExitCallback(exitCb) {
    if(!m_clickPositionCallback)
        throw std::runtime_error("Click callback is not set");

    if(!m_gameExitCallback)
        throw std::runtime_error("Quit Callback is not set");

    m_inputThread = std::thread(&GuiInput::inputLoop, this);
}

GuiInput::~GuiInput() {
    m_running = false;
    m_inputThread.join();
}

void GuiInput::inputLoop() {
    SDL_Event event;

    while (m_running) {
        while (SDL_WaitEvent(&event)) {
            if(event.syswm.type == SDL_QUIT){
                m_running = false;
                break;
            } else if(event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetGlobalMouseState(&mouseX,&mouseY);
                m_clickPositionCallback(mouseX, mouseY);
            }
        }
    }
    m_gameExitCallback();
}
