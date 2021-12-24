#pragma once

#include "IUserIO.h"
#include "GuiRenderer.h"

#include <memory>

class Gui : public IUserIO
{
public:
    Gui();

    void displayBoard(ChessBoard const& board) override;
    void startInputCapture() override;
    void setClickedPositionCallback(std::function<void(Position)> f) override;
    void setGameExitCallback(std::function<void()> f) override;

private:
    std::function<void(Position)> m_clickPositionCallback{nullptr};
    std::function<void()> m_gameExitCallback{nullptr};

    std::unique_ptr<GuiRenderer> m_render;
};
