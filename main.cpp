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

    Button increasePathDrawingDelayButton(900, 650, 50, 50, ButtonType::INCREASE_DARK);
    increasePathDrawingDelayButton.on_click([&board]() -> void {
                                          board.set_path_drawing_delay(board.get_path_drawing_delay() + 10);
                                      });

    Button decreasePathDrawingDelayButton(800, 650, 50, 50, ButtonType::DECREASE_DARK);
    decreasePathDrawingDelayButton.on_click([&board]() -> void {
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
        increasePathDrawingDelayButton.handle_events();
        decreasePathDrawingDelayButton.handle_events();

        board.draw();
        board.draw_paths();
        board.draw_mouse_position();

        startButton.draw();
        increaseBoardSizeButton.draw();
        decreaseBoardSizeButton.draw();
        increasePathDrawingDelayButton.draw();
        decreasePathDrawingDelayButton.draw();
        SDLController::end_frame();
    }
}
