#pragma once

#include "ChessBoard.h"
#include "Position.h"

#include <functional>

class IUserIO {
public:
    virtual void setBoard(ChessBoard* board) = 0;
    virtual void startInputCapture() = 0;
};
