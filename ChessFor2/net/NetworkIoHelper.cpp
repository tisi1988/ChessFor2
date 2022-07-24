#include "NetworkIoHelper.h"

#include <stdexcept>

NetworkIoHelper::NetworkIoHelper(std::function<void(int, int)> clickCb,
                                 std::function<void()> exitCb)
    : m_clickPositionCallback(clickCb), m_gameExitCallback(exitCb) {
  if (!m_clickPositionCallback)
    throw std::runtime_error("Click callback is not set");

  if (!m_gameExitCallback)
    throw std::runtime_error("Quit Callback is not set");

  m_inputThread = std::thread(&NetworkIoHelper::inputLoop, this);
}

NetworkIoHelper::~NetworkIoHelper() {
  m_running = false;
  m_inputThread.join();
}

void NetworkIoHelper::inputLoop() {

  if (m_netCfg.getRole() == NetCfg::HOST) {
    // Open a TCP socket to listen
  } else {
    auto const hostIp = m_netCfg.getGameHostIp();
    // Open a TCP socket to host
  }

  while (m_running) {
  }
  m_gameExitCallback();
}
