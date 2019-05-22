#include "button.h"
#include "../sdlcontroller/sdlcontroller.h"

Button::Button(float x, float y, float width, float height, bool increaseKey)
{
    this->increaseKey = increaseKey;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Button::draw()
{
    SDLController::set_color(255, 255, 255);
    SDLController::render_rectangle(x, y, width, height);

    SDLController::set_color(0, 0, 0);
    SDLController::render_rectangle(x + 10, y + height / 2.2, width - 20, 5);

    if (increaseKey)
    {
        SDLController::render_rectangle(x + width / 2.2, y + 10, 5, height - 20);
    }
}

bool Button::is_clicked()
{
    if (SDLController::event_handler.type == SDL_MOUSEBUTTONDOWN && SDLController::event_handler.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_PollEvent(&SDLController::event_handler);
        SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
        SDL_PumpEvents();
        std::vector<int> mouse_pos = SDLController::get_mouse_position();
        const int mouse_x = mouse_pos[0];
        const int mouse_y = mouse_pos[1];
        return mouse_x > x && mouse_x < x + width && mouse_y > y && mouse_y < y + height;
    }

    return false;
}
