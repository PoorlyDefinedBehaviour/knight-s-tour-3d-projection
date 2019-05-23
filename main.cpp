#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "button/button.h"

int main()
{
  SDLController::create_window(1280, 720);
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  Board board;

  Button startButton(1200, 650, 50, 50, ButtonType::START);
  startButton.on_click([&]() -> void {
    board.find_knights_path();
  });

  Button increaseBoardSizeButton(1100, 650, 50, 50, ButtonType::INCREASE);
  increaseBoardSizeButton.on_click([&]() -> void {
    board.resize(board.get_size() + 1);
  });

  Button decreaseBoardSizeButton(1000, 650, 50, 50, ButtonType::DECREASE);
  decreaseBoardSizeButton.on_click([&]() -> void {
    board.resize(board.get_size() - 1);
  });

  Button increaseMinimumTourSteps(900, 650, 50, 50, ButtonType::INCREASE);
  increaseMinimumTourSteps.on_click([&]() -> void {
    board.set_mininum_tour_steps(board.get_minimum_tour_steps() + 1);
  });

  Button decreaseMinimumTourSteps(800, 650, 50, 50, ButtonType::DECREASE);
  decreaseMinimumTourSteps.on_click([&]() -> void {
    board.set_mininum_tour_steps(board.get_minimum_tour_steps() - 1);
  });

  while (true)
  {
    SDL_PumpEvents();
    SDLController::start_frame();
    SDLController::clear_screen();
    SDLController::handle_events();
    board.handle_events();
    startButton.handle_events();
    increaseBoardSizeButton.handle_events();
    decreaseBoardSizeButton.handle_events();
    increaseMinimumTourSteps.handle_events();
    decreaseMinimumTourSteps.handle_events();

    board.draw_2d();
    board.draw_knights_path_2d();

    board.draw_3d();
    board.draw_knights_path_3d();

    board.draw_mouse_position();

    startButton.draw();
    increaseBoardSizeButton.draw();
    decreaseBoardSizeButton.draw();
    increaseMinimumTourSteps.draw();
    decreaseMinimumTourSteps.draw();

    SDLController::update_screen();
    SDLController::end_frame();
  }
}
