#ifndef GAME_H
#define GAME_H
#include "SDL2/include/SDL.h"

const int FPS = 30;
const float FRMAE_PER_MILLISECOND = 1000.0f / FPS;

class Game
{
private:
    bool isRunning = false;
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

public:
    Game();
    ~Game();

    void initialize();
    void run();
    void processInput();
    void update();
    void render();
    void destroy();
};

#endif