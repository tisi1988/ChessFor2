#include "NetworkIoHelper.h"

#include <stdexcept>

extern "C" {
#include <SDL2/SDL_net.h>
}

NetworkIoHelper::NetworkIoHelper(std::function<void(int, int)> clickCb,
                                 std::function<void()> exitCb)
    : m_clickPositionCallback(clickCb), m_gameExitCallback(exitCb) {

  if (SDLNet_Init() == -1) {
    throw std::runtime_error("SDLNet_Init error " +
                             std::string(SDLNet_GetError()));
  }

  if (!m_clickPositionCallback) {
    throw std::runtime_error("Click callback is not set");
  }

  if (!m_gameExitCallback) {
    throw std::runtime_error("Quit Callback is not set");
  }

  m_inputThread = std::thread(&NetworkIoHelper::inputLoop, this);
}

NetworkIoHelper::~NetworkIoHelper() {
  m_running = false;
  m_inputThread.join();
}

void NetworkIoHelper::inputLoop() {

  if (m_netCfg.getRole() == NetCfg::HOST) {
    // Open a TCP socket to listen
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, 8099) == -1) {
      fprintf(stderr, "ER: SDLNet_ResolveHost: %sn", SDLNet_GetError());
      exit(-1);
    }

    auto server_socket = SDLNet_TCP_Open(&ip);
    if (server_socket == NULL) {
      fprintf(stderr, "ER: SDLNet_TCP_Open: %sn", SDLNet_GetError());
      exit(-1);
    }

    auto socket_set = SDLNet_AllocSocketSet(1 + 1);
    if (socket_set == NULL) {
      throw std::runtime_error("Error allocating the server socket");
    }

    if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1) {
      throw std::runtime_error("Error opening the server soocket");
    }

    while (m_running) {
      int num_rdy = SDLNet_CheckSockets(socket_set, 1000);

      if (num_rdy <= 0) {
        // NOTE: none of the sockets are ready
      } else {
        // NOTE: some number of the sockets are ready
      }
    }
  } else {
    auto const hostIp = m_netCfg.getGameHostIp();
    // Open a TCP socket to host
  }

  while (m_running) {
  }
  m_gameExitCallback();
}
