#pragma once

#define SDL_MAIN_HANDLED
#include "../include/SDL2/SDL.h"
#include "../vector/vector.h"
#include <vector>

class SDLController
{
public:
    SDLController() = delete;
    static void create_window(const int &_width, const int &_height, const bool &fullscreen = false);
    static SDL_Texture *load_image(const char *file);
    static void handle_events(std::vector<Vector> &points);
    static void connect(int i, int j, const std::vector<Vector> &vertices);
    static void render(SDL_Texture *texture,
                       SDL_Rect *destination,
                       SDL_Rect *source = nullptr,
                       const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    static void render_rectangle(const float &x, const float &y, const int &width, const int &height);
    static void render_shape(const std::vector<Vector> vertices);
    static void render_point(int x, int y);
    static void render_line(int x1, int y1, int x2, int y2);
    static void render_lines(SDL_Point points[], int count);
    static void set_color(const int &r, const int &g, const int &b, const int &a = 0);
    static void clear_screen(int r = 0, int g = 0, int b = 0);
    static void update_screen();
    static void exit();

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;

private:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
};
