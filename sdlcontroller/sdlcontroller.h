#pragma once

#define SDL_MAIN_HANDLED
#include "../include/SDL2/SDL.h"

class SDLController
{
public:
    SDLController() = delete;
    static void init(const int &_width, const int &_height, const bool &fullscreen = false);
    static SDL_Texture *loadImage(const char *file);
    static void handleEvents();
    static void render(SDL_Texture *texture,
                       SDL_Rect *destination,
                       SDL_Rect *source = nullptr,
                       const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    static void renderRectangle(const int &width, const int &height, const float &x, const float &y);
    static void setRendererColor(const int &r, const int &g, const int &b, const int &a = 0);
    static void updateScreen();
    static void exit();

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;

private:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
};
