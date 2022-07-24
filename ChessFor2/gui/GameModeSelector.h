#pragma once

class GameModeSelector {
public:
  enum GameMode { LOCAL, LAN };

  static GameMode ask();
};
