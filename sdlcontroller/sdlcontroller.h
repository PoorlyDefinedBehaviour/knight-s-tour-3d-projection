#pragma once

#define SDL_MAIN_HANDLED
#include "../include/SDL2/SDL.h"
#include "../vector/vector.h"
#include "../matrix/matrix.h"
#include <vector>
#include <tuple>

class SDLController
{
public:
    SDLController() = delete;
    static void create_window(const int &_width, const int &_height, const bool &fullscreen = false);
    static void sleep(int ms);
    static SDL_Texture *load_image(const char *file);
    static void handle_events();
    static void connect(int i, int j, const std::vector<Vector3D> &vertices);
    static void render(SDL_Texture *texture,
                       SDL_Rect *destination,
                       SDL_Rect *source = nullptr,
                       const SDL_RendererFlip &flip = SDL_FLIP_NONE);
    static void render_rectangle(const float &x, const float &y, const int &width, const int &height);
    static void render_shape(const std::vector<Vector3D> vertices);
    static void render_point(int x, int y);
    static void render_line(int x1, int y1, int x2, int y2);
    static void render_lines(SDL_Point points[], int count);
    static void set_color(const int &r, const int &g, const int &b, const int &a = 0);
    static std::vector<int> get_mouse_position();
    static void clear_screen(int r = 0, int g = 0, int b = 0);
    static void update_screen();
    static void rotate(float x, float y, float z);
    static void exit();

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;
    static Matrix projection;
    static Matrix perspective;
    static Matrix isometric;
    static Matrix rotation_z;
    static Matrix rotation_x;
    static Matrix rotation_y;
    static std::vector<Vector3D> basic_cube_vertices;
    static SDL_Event event_handler;

private:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
};
