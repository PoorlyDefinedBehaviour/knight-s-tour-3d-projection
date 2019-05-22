#pragma once

class Button
{
private:
    float x;
    float y;
    float width;
    float height;
    bool increaseKey;

public:
    Button(float x, float y, float width, float height, bool increaseKey);
    void draw();
    bool is_clicked();
};
