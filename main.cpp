#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "button/button.h"

int main()
{
    SDLController::create_window(1280, 720);
    Board board;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Button startButton(1200, 650, 50, 50, ButtonType::START);
    startButton.on_click([&]() -> void {
        board.find_knights_path();
    });

    Button toggleTourTypeButton(900, 650, 50, 50, ButtonType::TOGGLE);
    toggleTourTypeButton.on_click([&]() -> void {
        board.toggle_tour_type();
    });

    Button increaseButton(1100, 650, 50, 50, ButtonType::INCREASE);
    increaseButton.on_click([&]() -> void {
        board.resize(board.get_size() + 1);
    });

    Button decreaseButton(1000, 650, 50, 50, ButtonType::DECREASE);
    decreaseButton.on_click([&]() -> void {
        board.resize(board.get_size() - 1);
    });

    while (true)
    {
        SDL_PumpEvents();
        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events();
        board.handle_events();
        startButton.handle_events();
        toggleTourTypeButton.handle_events();
        increaseButton.handle_events();
        decreaseButton.handle_events();

        board.draw_2d();
        board.draw_knights_path_2d();

        board.draw_3d();
        board.draw_knights_path_3d();

        board.draw_mouse_position();

        startButton.draw();
        toggleTourTypeButton.draw();
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
