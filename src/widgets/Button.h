#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_ttf.h"

typedef enum
{
    BTN_STATE_NORMAL,  // 默认状态
    BTN_STATE_HOVER,   // 鼠标悬停
    BTN_STATE_PRESSED, // 鼠标按下
    BTN_STATE_DISABLED // 禁用状态
} ButtonState;

typedef struct
{
    SDL_Rect rect;
    ButtonState state;
    const char *text;
    SDL_Color bgColor;
    SDL_Color textColor;
    void (*onClick)(); // 点击回调函数

} Button;

Button craeteButton(int x, int y, int w, int h,
                    const char *text, SDL_Color bgColor, SDL_Color textColor, void (*clickHandler)());

void handleButtonEvent(Button *btn, SDL_Event *event);

void renderButton(SDL_Renderer *renderer, TTF_Font *font, Button *btn);

#endif // BUTTON_H