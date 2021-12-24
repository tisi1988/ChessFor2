#pragma once

#include "ChessBoard.h"
#include "Position.h"

#include <functional>

class IUserIO {
public:
    virtual void displayBoard(ChessBoard const& board) = 0;
    virtual void startInputCapture() = 0;
    virtual void  setClickedPositionCallback(std::function<void(Position)> f) = 0;
    virtual void  setGameExitCallback(std::function<void()> f) = 0;
};
