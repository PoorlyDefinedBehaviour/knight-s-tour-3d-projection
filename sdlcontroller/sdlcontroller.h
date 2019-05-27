#pragma once

#define SDL_MAIN_HANDLED
#include "../include/SDL2/SDL.h"
#include "../vector/vector.h"
#include "../matrix/matrix.h"
#include <tuple>

class SDLController
{
public:
    SDLController() = delete;
    static void create_window(const int &_width, const int &_height, const bool &fullscreen = false);
    static void update_screen();
    static void clear_screen(int r = 0, int g = 0, int b = 0);
    static void start_frame();
    static void end_frame();
    static void handle_events();

    static void sleep(size_t ms);
    static void exit();

    static void set_color(const int &r, const int &g, const int &b, const int &a = 0);
    static std::pair<int, int> get_mouse_position();

    static void render_rectangle(float x, float y, int width, int height);
    static void render_point(int x, int y);
    static void render_line(int x1, int y1, int x2, int y2);
    static void render_lines(SDL_Point points[], int count);

    static void render_shape(const std::vector<Vector3D> vertices);
    static void render_cube(float x, float y, float z, float size);
    static void rotate(float x, float y, float z);
    static void connect(size_t i, size_t j, const std::vector<Vector3D> &vertices);

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;
    static int WINDOW_HALF_WIDTH;
    static int WINDOW_HALF_HEIGHT;
    static Matrix<float> ortographic;
    static Matrix<float> rotation_z;
    static Matrix<float> rotation_x;
    static Matrix<float> rotation_y;
    static SDL_Event event_handler;

private:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
    static constexpr int FPS = 60;
    static constexpr int frameDelay = 1000 / FPS;
    static Uint32 frameStart;
    static Uint32 frameTime;
};
