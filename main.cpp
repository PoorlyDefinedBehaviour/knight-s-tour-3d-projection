#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "button/button.h"

int main()
{
    SDLController::create_window(1280, 720);

    Board board;

    Button startButton(1200, 650, 50, 50, ButtonType::START);
    startButton.on_click([&board]() -> void {
                             std::thread knights_tour_thread([&board]() -> void {
                                 board.find_knights_path();
                             });

                             knights_tour_thread.join();
                         });

    Button increaseBoardSizeButton(1100, 650, 50, 50, ButtonType::INCREASE_LIGHT);
    increaseBoardSizeButton.on_click([&board]() -> void {
                                         board.resize(board.get_size() + 1);
                                     });

    Button decreaseBoardSizeButton(1000, 650, 50, 50, ButtonType::DECREASE_LIGHT);
    decreaseBoardSizeButton.on_click([&board]() -> void {
                                         board.resize(board.get_size() - 1);
                                     });

    Button increasePathDrawingDelay(900, 650, 50, 50, ButtonType::INCREASE_DARK);
    increasePathDrawingDelay.on_click([&board]() -> void {
                                          board.set_path_drawing_delay(board.get_path_drawing_delay() + 10);
                                      });

    Button decreasePathDrawingDelay(800, 650, 50, 50, ButtonType::DECREASE_DARK);
    decreasePathDrawingDelay.on_click([&board]() -> void {
                                          board.set_path_drawing_delay(board.get_path_drawing_delay() - 10);
                                      });

    while (true)
    {
        SDLController::start_frame();
        SDLController::clear_screen();
        SDLController::handle_events();
        board.handle_events();
        startButton.handle_events();
        increaseBoardSizeButton.handle_events();
        decreaseBoardSizeButton.handle_events();
        increasePathDrawingDelay.handle_events();
        decreasePathDrawingDelay.handle_events();

        board.draw();
        board.draw_paths();
        board.draw_mouse_position();

        startButton.draw();
        increaseBoardSizeButton.draw();
        decreaseBoardSizeButton.draw();
        increasePathDrawingDelay.draw();
        decreasePathDrawingDelay.draw();
        SDLController::end_frame();
    }
}
