#include "sdlcontroller.h"

#include <cstdlib>
#include <vector>
#include <cmath>

SDL_Window *SDLController::window;
SDL_Renderer *SDLController::renderer;
SDL_Event SDLController::event_handler;
constexpr int SDLController::FPS;
constexpr int SDLController::frameDelay;
Uint32 SDLController::frameStart;
Uint32 SDLController::frameTime;
int SDLController::WINDOW_WIDTH;
int SDLController::WINDOW_HEIGHT;
int SDLController::WINDOW_HALF_WIDTH;
int SDLController::WINDOW_HALF_HEIGHT;
Matrix<float> SDLController::ortographic;
Matrix<float> SDLController::rotation_z;
Matrix<float> SDLController::rotation_x;
Matrix<float> SDLController::rotation_y;

void SDLController::create_window(const int &_width, const int &_height, const bool &fullscreen)
{
    WINDOW_WIDTH = _width;
    WINDOW_HEIGHT = _height;
    WINDOW_HALF_WIDTH = WINDOW_WIDTH / 2;
    WINDOW_HALF_HEIGHT = WINDOW_HEIGHT / 2;

    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen)
    {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, flags, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xb4, 0xff, 0xff);

    ortographic.resize(2, 3);
    rotation_z.resize(3, 3);
    rotation_x.resize(3, 3);
    rotation_y.resize(3, 3);

    ortographic.elements = {{1.0f, 0.0f, 0.0f},
                            {0.0f, 1, 0.0f}};

    rotation_z.elements = {
        {std::cos(0.0f), -std::sin(0.0f), 0.0f},
        {std::sin(0.0f), std::cos(0.0f), 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f}};

    rotation_x.elements = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, std::cos(0.0f), std::sin(0.0f)},
        {0.0f, -std::sin(0.0f), std::cos(0.0f)}};

    rotation_y.elements = {
        {std::cos(0.0f), 0.0f, std::sin(0.0f)},
        {0.0f, 1.0f, 0.0f},
        {-std::sin(0.0f), 0.0f, std::cos(0.0f)}};
}

void SDLController::sleep(size_t ms)
{
    SDL_Delay(ms);
}

void SDLController::handle_events()
{
    constexpr float rotation_speed = 0.01f;

    SDL_PollEvent(&event_handler);

    Uint8 *keysArray = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));

    if (event_handler.type == SDL_QUIT || keysArray[SDL_SCANCODE_ESCAPE])
    {
        SDLController::exit();
    }

    if (keysArray[SDL_SCANCODE_R])
    {
        rotate(rotation_speed, 0, 0);
    }

    if (keysArray[SDL_SCANCODE_T])
    {
        rotate(-rotation_speed, 0, 0);
    }

    if (keysArray[SDL_SCANCODE_F])
    {
        rotate(0, rotation_speed, 0);
    }

    if (keysArray[SDL_SCANCODE_G])
    {
        rotate(0, -rotation_speed, 0);
    }

    if (keysArray[SDL_SCANCODE_V])
    {
        rotate(0, 0, rotation_speed);
    }

    if (keysArray[SDL_SCANCODE_B])
    {
        rotate(0, 0, -rotation_speed);
    }
}

void SDLController::rotate(float x, float y, float z)
{
    static float x_angle = 0.0f;
    static float y_angle = 0.0f;
    static float z_angle = 0.0f;

    x_angle += x;
    y_angle += y;
    z_angle += z;

    rotation_x.elements = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, std::cos(x_angle), std::sin(x_angle)},
        {0.0f, -std::sin(x_angle), std::cos(x_angle)}};

    rotation_z.elements = {
        {std::cos(z_angle), -std::sin(z_angle), 0.0f},
        {std::sin(z_angle), std::cos(z_angle), 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f}};

    rotation_y.elements = {
        {std::cos(y_angle), 0.0f, std::sin(y_angle)},
        {0.0f, 1.0f, 0.0f},
        {-std::sin(y_angle), 0.0f, std::cos(y_angle)}};
}

void SDLController::set_color(const int &r, const int &g, const int &b, const int &a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

std::pair<int, int> SDLController::get_mouse_position()
{
    int x_pos;
    int y_pos;

    SDL_GetMouseState(&x_pos, &y_pos);
    return std::make_pair(x_pos, y_pos);
}

void SDLController::render_rectangle(float x, float y, int width, int height)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;

    SDL_RenderFillRect(renderer, &rectangle);
}

void SDLController::render_cube(float x, float y, float z, float size)
{
    std::vector<Vector3D> cube_vertices = {
        Vector3D(0.0f, 0.0f, 0.0f),
        Vector3D(size, 0.0f, 0.0f),
        Vector3D(size, size, 0.0f),
        Vector3D(0.0f, size, 0.0f),
        Vector3D(0.0f, 0.0f, size),
        Vector3D(size, 0.0f, size),
        Vector3D(size, size, size),
        Vector3D(0.0f, size, size)};

    std::vector<Vector3D> projected_points;
    projected_points.reserve(cube_vertices.size());

    for (auto point : cube_vertices)
    {
        point.translate(x, y, z);
        auto projection = ortographic * rotation_x * rotation_y * rotation_z * point;
        projected_points.emplace_back(projection.to_vector3d());
    }

    render_shape(projected_points);
}

void SDLController::render_shape(const std::vector<Vector3D> vertices)
{
    const auto num_vertices = vertices.size();
    for (size_t i = 0; i < num_vertices / 2; i++)
    {
        connect(i, (i + 1) % (num_vertices / 2), vertices);
        connect(i + (num_vertices / 2), ((i + 1) % (num_vertices / 2)) + (num_vertices / 2), vertices);
        connect(i, i + (num_vertices / 2), vertices);
    }
}

void SDLController::connect(size_t i, size_t j, const std::vector<Vector3D> &vertices)
{
    Vector3D a = vertices[i];
    Vector3D b = vertices[j];
    render_line(a.x, a.y, b.x, b.y);
}

void SDLController::render_point(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}

void SDLController::render_line(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SDLController::render_lines(SDL_Point points[], int count)
{
    SDL_RenderDrawLines(renderer, points, count);
}

void SDLController::clear_screen(int r, int g, int b)
{
    SDL_RenderClear(renderer);
    set_color(r, g, b);
    render_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void SDLController::update_screen()
{
    SDL_RenderPresent(renderer);
}

void SDLController::start_frame()
{
    SDL_PumpEvents();
    frameStart = SDL_GetTicks();
}

void SDLController::end_frame()
{
    update_screen();
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
    {
        SDL_Delay(frameDelay - frameTime);
    }
}

void SDLController::exit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
}
