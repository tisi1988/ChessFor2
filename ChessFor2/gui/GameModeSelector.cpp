#include "GameModeSelector.h"

#include <iostream>

extern "C" {
#include <SDL_messagebox.h>
}

GameModeSelector::GameMode GameModeSelector::ask() {
  const SDL_MessageBoxButtonData buttons[] = {
      {0, 0, "Local game"},
      {0, 1, "Network game"},
  };

  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION,               /* .flags */
      NULL,                                     /* .window */
      "Game mode selection",                    /* .title */
      "What kind of game do you want to play?", /* .message */
      SDL_arraysize(buttons),                   /* .numbuttons */
      buttons,                                  /* .buttons */
      NULL                                      /* .colorScheme */
  };

  int buttonid = -1;
  auto const ret = SDL_ShowMessageBox(&messageboxdata, &buttonid);
  if (ret < 0) {
    std::cerr << "Error creating the dialog to ask the game mode" << std::endl;
  }

  return buttonid == 0 ? GameMode::LOCAL : GameMode::LAN;
}
