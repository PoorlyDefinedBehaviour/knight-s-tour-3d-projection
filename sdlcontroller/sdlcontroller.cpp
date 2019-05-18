#include "sdlcontroller.h"

#include <cstdlib>
#include <vector>

SDL_Window *SDLController::window;
SDL_Renderer *SDLController::renderer;
int SDLController::WINDOW_WIDTH;
int SDLController::WINDOW_HEIGHT;

void SDLController::create_window(const int &_width, const int &_height, const bool &fullscreen)
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    WINDOW_WIDTH = _width;
    WINDOW_HEIGHT = _height;

    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen)
    {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    window = SDL_CreateWindow("Knight's Tour",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              _width,
                              _height,
                              flags);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xb4, 0xff, 0xff);
}

SDL_Texture *SDLController::load_image(const char *file)
{
    /*
    SDL_Surface* tempImage = IMG_Load(file);
    SDL_Surface* optimizedImage = SDL_ConvertSurface(tempImage, tempImage->format, 0);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, optimizedImage);

    SDL_FreeSurface(tempImage);
    SDL_FreeSurface(optimizedImage);

    return texture;
    */
    return nullptr;
}

void SDLController::handle_events()
{
    SDL_Event event;
    SDL_PumpEvents();
    SDL_PollEvent(&event);

    Uint8 *keysArray = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));

    if (event.type == SDL_QUIT || keysArray[SDL_SCANCODE_ESCAPE])
    {
        SDLController::exit();
    }
}

void SDLController::set_color(const int &r, const int &g, const int &b, const int &a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
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

void SDLController::exit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
}
