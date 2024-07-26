#include "TcpServer.h"

extern "C" {
#include <SDL2/SDL_net.h>
}

#include <iostream>
#include <stdexcept>

TcpServer::TcpServer(int port) : m_port(port), m_finish(false) {}

void TcpServer::listen() {
  TCPsocket server, client;
  IPaddress ip;
  if (SDLNet_ResolveHost(&ip, NULL, m_port) == -1) {
    throw std::runtime_error("Error allocating the server socket " +
                             std::string(SDLNet_GetError()));
  }
  server = SDLNet_TCP_Open(&ip);
  if (!server) {
    throw std::runtime_error("Error opening the server socket " +
                             std::string(SDLNet_GetError()));
  }

  do {
    /* try to accept a connection */
    client = SDLNet_TCP_Accept(server);
  } while (!client && []() -> bool {
    SDL_Delay(100);
    return true;
  }());

  /* get the clients IP and port number */
  IPaddress *remoteip;
  remoteip = SDLNet_TCP_GetPeerAddress(client);
  if (!remoteip) {
    throw std::runtime_error("Could not get the client IP " +
                             std::string(SDLNet_GetError()));
  }

  /* print out the clients IP and port number */
  Uint32 const ipaddr = SDL_SwapBE32(remoteip->host);
  std::cout << "Client IP is " << (ipaddr >> 24) << "."
            << ((ipaddr >> 16) & 0xff) << "." << ((ipaddr >> 8) & 0xff) << "."
            << (ipaddr & 0xff) << ":" << remoteip->port << std::endl;

  while (!m_finish) {

    /* read the buffer from client */
    char message[1024];
    int const len = SDLNet_TCP_Recv(client, message, 1024);
    if (!len) {
      std::cerr << "SDLNet_TCP_Recv: %s" << SDLNet_GetError();
      break;
    }

    // TODO handle message
  }

  SDLNet_TCP_Close(client);
}

void TcpServer::stop() { m_finish = true; }
