#include "Button.h"

Button craeteButton(int x, int y, int w, int h,
                    const char *text, SDL_Color bgColor, SDL_Color textColor, void (*clickHandler)())
{
    Button btn;
    btn.rect = {x, y, w, h};
    btn.text = text;
    btn.bgColor = bgColor;
    btn.textColor = textColor;
    btn.state = BTN_STATE_NORMAL;
    btn.onClick = clickHandler;
    return btn;
}

void handleButtonEvent(Button *btn, SDL_Event *event)
{
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
    {
        int mouseX = event->motion.x;
        int mouseY = event->motion.y;

        SDL_GetMouseState(&mouseX, &mouseY);
        bool isInside = (mouseX >= btn->rect.x) && (mouseX <= btn->rect.x + btn->rect.w) &&
                        (mouseY >= btn->rect.y) && (mouseY <= btn->rect.y + btn->rect.h);

        if (isInside)
        {
            if (event->type == SDL_MOUSEBUTTONDOWN)
            {
                btn->state = BTN_STATE_PRESSED;
            }
            else if (event->type == SDL_MOUSEBUTTONUP && btn->state == BTN_STATE_PRESSED)
            {
                btn->onClick(); // 触发点击回调
                btn->state = BTN_STATE_HOVER;
            }
            else
            {
                btn->state = BTN_STATE_HOVER;
            }
        }
        else
        {
            btn->state = BTN_STATE_NORMAL;
        }
    }
}

void renderButton(SDL_Renderer *renderer, TTF_Font *font, Button *btn)
{
    SDL_Color finalBgColor = btn->bgColor;
    if (btn->state == BTN_STATE_HOVER)
    {
        finalBgColor = {200, 200, 200, 255}; // 悬停颜色
    }
    else if (btn->state == BTN_STATE_PRESSED)
    {
        finalBgColor = {150, 150, 150, 255}; // 按下颜色
    }

    SDL_SetRenderDrawColor(renderer, finalBgColor.r, finalBgColor.g, finalBgColor.b, finalBgColor.a);
    SDL_RenderFillRect(renderer, &btn->rect);

    // 绘制文字
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, btn->text, btn->textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {
        btn->rect.x + (btn->rect.w - textSurface->w) / 2, // horizontally centered
        btn->rect.y + (btn->rect.h - textSurface->h) / 2, // vertically centered
        textSurface->w,
        textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}