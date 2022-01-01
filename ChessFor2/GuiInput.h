#pragma once

#include <atomic>
#include <functional>
#include <thread>

class GuiInput {
public:
  GuiInput(std::function<void(int, int)> clickCb, std::function<void()> exitCb);
  ~GuiInput();

private:
  void inputLoop();

  std::function<void(int, int)> m_clickPositionCallback{nullptr};
  std::function<void()> m_gameExitCallback{nullptr};

  std::atomic_bool m_running{true};
  std::thread m_inputThread;
};
