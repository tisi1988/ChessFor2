#include <iostream>

#include <SDL_version.h>

int main() {
  SDL_version sdlVersion;
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
           compiled.major, compiled.minor, compiled.patch);
    printf("We linked against SDL version %d.%d.%d.\n",
           linked.major, linked.minor, linked.patch);
}

