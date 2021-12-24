#include "ChessFor2.h"
#include "Gui.h"

#include <iostream>

ChessFor2::ChessFor2()
{
    try{
        m_io = std::make_unique<Gui>();
    }catch(std::runtime_error const& e) {
        std::cout << "Error initializing: " << e.what() << std::endl;
    }
}

void ChessFor2::run() {
    while(true) {
    }
}
