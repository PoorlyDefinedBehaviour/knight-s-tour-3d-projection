#include "button.h"
#include "../sdlcontroller/sdlcontroller.h"

Button::Button(float x, float y, float width, float height, ButtonType type)
{
    this->type = type;
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

    if (this->type == ButtonType::START)
    {
        SDLController::set_color(0, 255, 0);
        SDLController::render_rectangle(x + 15, y + 15, width - 30, height - 30);
    }

    if (this->type == ButtonType::TOGGLE)
    {
        SDLController::set_color(255, 0, 137);
        SDLController::render_rectangle(x + 15, y + 15, width - 30, height - 30);
    }

    if (this->type == ButtonType::INCREASE)
    {
        SDLController::render_rectangle(x + 10, y + height / 2.2, width - 20, 5);
        SDLController::render_rectangle(x + width / 2.2, y + 10, 5, height - 20);
        return;
    }

    if (this->type == ButtonType::DECREASE)
    {
        SDLController::render_rectangle(x + 10, y + height / 2.2, width - 20, 5);
        return;
    }
}

void Button::handle_events()
{
    if (SDLController::event_handler.type == SDL_MOUSEBUTTONDOWN && SDLController::event_handler.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_PollEvent(&SDLController::event_handler);
        SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
        SDL_PumpEvents();
        std::vector<int> mouse_pos = SDLController::get_mouse_position();
        const int &mouse_x = mouse_pos.front();
        const int &mouse_y = mouse_pos.back();
        if (mouse_x > x && mouse_x < x + width && mouse_y > y && mouse_y < y + height)
            click_handler();
    }
}

void Button::on_click(const std::function<void(void)> &click_handler)
{
    this->click_handler = click_handler;
}
