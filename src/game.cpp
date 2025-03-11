#include <iostream>
#include "game.h"
#include "widgets/Button.h"
#include "logger/Logger.h"
#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_image.h"
#include "SDL2/include/SDL_mixer.h"

Game::Game()
{
    std::cout << "Game::Game()" << std::endl;
    initialize();
}

void Game::initialize()
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
        return;
    }
    // 设置窗口为全屏
    SDL_DisplayMode m_displayMode;
    SDL_GetCurrentDisplayMode(0, &m_displayMode);
    SDL_Log("SDL get display mode: %d x %d @ %d Hz", m_displayMode.w, m_displayMode.h, m_displayMode.refresh_rate);

    // 创建窗口，窗口居中
    m_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_displayMode.w, m_displayMode.h, SDL_WINDOW_BORDERLESS);

    if (!m_window)
    {
        SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
        return;
    }
    // 创建渲染器
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        SDL_Log("Renderer could not be created! SDL Error: %s", SDL_GetError());
        return;
    }

    // 初始化图片库
    IMG_Init(IMG_INIT_PNG);
    // if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    // {
    //     SDL_Log("SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
    //     return;
    // }

    // 初始化音频
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        SDL_Log("Mix_OpenAudio error: %s", Mix_GetError());
        return;
    }
    Mix_Music *music = Mix_LoadMUS("./assets/audios/1.mp3");
    // 播放背景音乐
    Mix_PlayMusic(music, -1);

    // 设置窗口为全屏展示
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

    // 初始化 TTF
    TTF_Init();
    m_font = TTF_OpenFont("./assets/fonts/ARIAL.TTF", 24);
    if (m_font == nullptr)
    {
        Logger::LogErr("TTF_OpenFont error:");
        return;
    }
    // 渲染按钮
    btn = craeteButton(100, 100, 100, 50, "Hello World", {255, 0, 0, 255}, {255, 255, 255, 255}, []()
                       { Logger::LogInfo("Button clicked"); });

    isRunning = true;
    SDL_Log("SDL initialized successfully");
    Logger::LogInfo("SDL initialized successfully ....");
}

void Game::run()
{
    while (isRunning)
    {
        processInput();
        update();
        render();
    }
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleButtonEvent(&btn, &event);
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
            // 判断是否按下了 ESC 键
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
                break;
            }

        default:
            break;
        }
    }
}

std::pair<int, int> initPosition = {10, 10};
int floatSpeed = 1;
void Game::update()
{

    // 更新的时候控制帧率
    //  int currentTimestamp = SDL_GetTicks();

    initPosition.first += floatSpeed;
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer); // 用给的颜色填充整个渲染区

    // 绘制矩形
    SDL_Rect rect = {10, 10, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, &rect);

    // 绘制图片
    SDL_Surface *surface = IMG_Load("./assets/images/tank_left.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface); // 释放图片纹理
    // 绘制图片到指定位置

    SDL_Rect dstRect = {initPosition.first, initPosition.second, surface->w, surface->h};
    SDL_RenderCopy(m_renderer, texture, NULL, &dstRect);

    // 绘制按钮和文字
    renderButton(m_renderer, m_font, &btn);

    SDL_RenderPresent(m_renderer); // 显示渲染结果
}

void Game::destroy()
{
    // 释放 SDL 资源
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    // 销毁窗口
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    // 释放TTF
    TTF_CloseFont(m_font);
    m_font = nullptr;
    TTF_Quit();

    // 退出 SDL
    SDL_Quit();
}

Game::~Game()
{
    std::cout << "Game::~Game()" << std::endl;
    destroy();
}
