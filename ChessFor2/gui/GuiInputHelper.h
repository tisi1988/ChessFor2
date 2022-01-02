#pragma once

#include <atomic>
#include <functional>
#include <thread>

/**
 * @brief The GuiInputHelper class implements
 * the user input handling.
 */
class GuiInputHelper {
public:
  /**
   * @brief GuiInputHelper constructor.
   * @param clickCb Callback for user click.
   * @param exitCb Callback for game exit.
   */
  GuiInputHelper(std::function<void(int, int)> clickCb,
                 std::function<void()> exitCb);
  ~GuiInputHelper();

private:
  void inputLoop();

  std::function<void(int, int)> m_clickPositionCallback{nullptr};
  std::function<void()> m_gameExitCallback{nullptr};

  std::atomic_bool m_running{true};
  std::thread m_inputThread;
};
