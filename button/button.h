#pragma once
#include <functional>

enum class ButtonType
{
    START,
    TOGGLE,
    INCREASE_DARK,
    DECREASE_DARK,
    INCREASE_LIGHT,
    DECREASE_LIGHT
};

class Button
{
private:
    float x;
    float y;
    float width;
    float height;
    ButtonType type;
    std::function<void(void)> click_handler;

public:
    Button(float x, float y, float width, float height, ButtonType type);
    void draw() const;
    void handle_events();
    void on_click(const std::function<void(void)> &click_handler);
};
