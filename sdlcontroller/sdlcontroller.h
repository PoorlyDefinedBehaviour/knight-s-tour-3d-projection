#pragma once

#define SDL_MAIN_HANDLED
#include "../include/SDL2/SDL.h"

class SDLController
{
public:
    SDLController() = delete;
    static void create_window(const int &_width, const int &_height, const bool &fullscreen = false);
    static SDL_Texture *load_image(const char *file);
    static void handle_events();
    static void render(SDL_Texture *texture,
                       SDL_Rect *destination,
                       SDL_Rect *source = nullptr,
                       const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    static void render_rectangle(const int &width, const int &height, const float &x, const float &y);
    static void render_line(int x1, int y1, int x2, int y2);
    static void render_lines(SDL_Point points[], int count);
    static void set_color(const int &r, const int &g, const int &b, const int &a = 0);
    static void clear_screen();
    static void update_screen();
    static void exit();

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;

private:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
};
