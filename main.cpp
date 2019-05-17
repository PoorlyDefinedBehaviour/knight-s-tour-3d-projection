#include <iostream>
#include <vector>
#include <algorithm>
#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "knight/knight.h"

int main()
{
    SDLController::create_window(800, 800);
    Board board;
    board.resize(8);

    Knight black_knight;
    black_knight.tour(&board);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (true)
    {
        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events();
        board.draw();
        black_knight.show_path();
        SDLController::update_screen();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
