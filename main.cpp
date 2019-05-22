#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "button/button.h"

int main()
{
    SDLController::create_window(1280, 720);
    Board board;
    board.find_knights_path();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Button increaseButton(1100, 650, 50, 50, true);
    Button decreaseButton(1000, 650, 50, 50, false);

    while (true)
    {
        SDL_PumpEvents();
        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events();

        if (increaseButton.is_clicked())
        {
            std::cout << "increaseButton clicked" << '\n';
            board.resize(board.get_size() + 1);
            board.find_knights_path();
        }

        if (decreaseButton.is_clicked())
        {
            std::cout << "decreaseButton clicked" << '\n';
            board.resize(board.get_size() - 1);
            board.find_knights_path();
        }

        board.draw_2d();
        board.draw_knights_path_2d();

        board.draw_3d();
        board.draw_knights_path_3d();

        decreaseButton.draw();
        increaseButton.draw();

        SDLController::update_screen();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
