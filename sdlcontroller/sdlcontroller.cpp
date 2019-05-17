#include "sdlcontroller.h"

#include <cstdlib>

SDL_Window *SDLController::window;
SDL_Renderer *SDLController::renderer;
int SDLController::WINDOW_WIDTH;
int SDLController::WINDOW_HEIGHT;

void SDLController::init(const int &_width, const int &_height, const bool &fullscreen)
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

SDL_Texture *SDLController::loadImage(const char *file)
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

void SDLController::handleEvents()
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

void SDLController::setRendererColor(const int &r, const int &g, const int &b, const int &a)
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

void SDLController::renderRectangle(const int &width, const int &height, const float &x, const float &y)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;

    SDL_RenderFillRect(renderer, &rectangle);
}

void SDLController::updateScreen()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void SDLController::exit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
}
