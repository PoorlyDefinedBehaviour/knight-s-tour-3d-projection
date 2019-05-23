#include "sdlcontroller.h"

#include <cstdlib>
#include <vector>
#include <cmath>

SDL_Window *SDLController::window;
SDL_Renderer *SDLController::renderer;
SDL_Event SDLController::event_handler;
const int SDLController::FPS;
const int SDLController::frameDelay;
Uint32 SDLController::frameStart;
int SDLController::frameTime;
int SDLController::WINDOW_WIDTH;
int SDLController::WINDOW_HEIGHT;
int SDLController::WINDOW_HALF_WIDTH;
int SDLController::WINDOW_HALF_HEIGHT;
Matrix<float> SDLController::projection;
Matrix<float> SDLController::perspective;
Matrix<float> SDLController::isometric;
Matrix<float> SDLController::rotation_z;
Matrix<float> SDLController::rotation_x;
Matrix<float> SDLController::rotation_y;
std::vector<Vector3D> SDLController::basic_cube_vertices;

void SDLController::create_window(const int &_width, const int &_height, const bool &fullscreen)
{
  //ShowWindow(GetConsoleWindow(), SW_HIDE);

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

  window = SDL_CreateWindow("Knight's Tour",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            _width,
                            _height,
                            flags);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xb4, 0xff, 0xff);

  projection.resize(2, 3);
  perspective.resize(3, 3);
  isometric.resize(3, 3);
  rotation_z.resize(3, 3);
  rotation_x.resize(3, 3);
  rotation_y.resize(3, 3);

  projection.elements = {{1.0f, 0.0f, 0.0f},
                         {0.0f, 1, 0.0f}};

  perspective.elements = {
      {1.0f, 0.0f, 0.0f},
      {0.0f, 4.0f / 3.0f, 0.0f},
      {0.0f, 0.0f, 1.0f}};

  isometric.elements = {
      {1.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, std::cos(0.0f), std::sin(0.0f)},
      {0.0f, -std::sin(0.0f), std::cos(0.0f)}};

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

  basic_cube_vertices = {
      Vector3D(-50.0f, -50.0f, -50.0f),
      Vector3D(50.0f, -50.0f, -50.0f),
      Vector3D(50.0f, 50.0f, -50.0f),
      Vector3D(-50.0f, 50.0f, -50.0f),
      Vector3D(-50.0f, -50.0f, 50.0f),
      Vector3D(50.0f, -50.0f, 50.0f),
      Vector3D(50.0f, 50.0f, 50.0f),
      Vector3D(-50.0f, 50.0f, 50.0f)};
}

void SDLController::sleep(int ms)
{
  SDL_Delay(ms);
}

void SDLController::handle_events()
{
  SDL_PumpEvents();
  SDL_PollEvent(&event_handler);

  const float rotation_speed = 0.01f;
  const float cube_movement_speed = 10.0f;

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

  if (keysArray[SDL_SCANCODE_D])
  {
    for (auto &point : basic_cube_vertices)
      point.x += cube_movement_speed;
  }

  if (keysArray[SDL_SCANCODE_A])
  {
    for (auto &point : basic_cube_vertices)
      point.x -= cube_movement_speed;
  }

  if (keysArray[SDL_SCANCODE_S])
  {
    for (auto &point : basic_cube_vertices)
      point.y += cube_movement_speed;
  }

  if (keysArray[SDL_SCANCODE_W])
  {
    for (auto &point : basic_cube_vertices)
      point.y -= cube_movement_speed;
  }

  if (keysArray[SDL_SCANCODE_X])
  {
    for (auto &point : basic_cube_vertices)
      point.z += cube_movement_speed;
  }

  if (keysArray[SDL_SCANCODE_Z])
  {
    for (auto &point : basic_cube_vertices)
      point.z -= cube_movement_speed;
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

void SDLController::connect(int i, int j, const std::vector<Vector3D> &vertices)
{
  Vector3D a = vertices[i];
  Vector3D b = vertices[j];
  SDLController::render_line(a.x, a.y, b.x, b.y);
}

void SDLController::set_color(const int &r, const int &g, const int &b, const int &a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

std::pair<int, int> SDLController::get_mouse_position()
{
  int x_pos = NULL;
  int y_pos = NULL;

  SDL_GetMouseState(&x_pos, &y_pos);
  return std::make_pair(x_pos, y_pos);
}

void SDLController::render(SDL_Texture *texture, SDL_Rect *source, SDL_Rect *destination, const SDL_RendererFlip &flip)
{
  if (!source || source->w < 0 || source->h < 0)
  {
    SDL_RenderCopyEx(renderer, texture, nullptr, destination, NULL, nullptr, flip);
  }
  else
  {
    SDL_RenderCopyEx(renderer, texture, source, destination, NULL, nullptr, flip);
  }
}

void SDLController::render_rectangle(const float &x, const float &y, const int &width, const int &height)
{
  SDL_Rect rectangle;
  rectangle.x = x;
  rectangle.y = y;
  rectangle.w = width;
  rectangle.h = height;

  SDL_RenderFillRect(renderer, &rectangle);
}

void SDLController::render_shape(const std::vector<Vector3D> vertices)
{
  const auto num_vertices = vertices.size();
  for (auto i = 0; i < num_vertices / 2; i++)
  {
    connect(i, (i + 1) % (num_vertices / 2), vertices);
    connect(i + (num_vertices / 2), ((i + 1) % (num_vertices / 2)) + (num_vertices / 2), vertices);
    connect(i, i + (num_vertices / 2), vertices);
  }
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
