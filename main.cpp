#include <iostream>
#include <vector>
#include <cmath>
#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "vector/vector.h"

int main()
{
    SDLController::create_window(1280, 720);
    Board board;
    board.resize(8);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    board.knight_tour();

    while (true)
    {
        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events();
        SDLController::update_view_matrices();

        board.draw_2d();
        board.draw_knights_path_2d();

        board.draw_3d();
        board.draw_knights_path_3d();

        SDLController::update_screen();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
