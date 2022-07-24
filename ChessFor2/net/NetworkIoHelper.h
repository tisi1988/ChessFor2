#pragma once

#include "NetCfg.h"

#include <atomic>
#include <functional>
#include <thread>

class NetworkIoHelper {
public:
  /**
   * @brief GuiInputHelper constructor.
   * @param clickCb Callback for user click.
   * @param exitCb Callback for game exit.
   */
  NetworkIoHelper(std::function<void(int, int)> clickCb,
                  std::function<void()> exitCb);

  ~NetworkIoHelper();

private:
  void inputLoop();

  std::function<void(int, int)> m_clickPositionCallback{nullptr};
  std::function<void()> m_gameExitCallback{nullptr};

  std::atomic_bool m_running{true};
  std::thread m_inputThread;

  NetCfg m_netCfg;
};
