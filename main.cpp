#include <iostream>
#include <vector>
#include <cmath>
#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "knight/knight.h"
#include "vector/vector.h"

float angle = 0;

void update_matrices(Matrix &rotation_x, Matrix &rotation_y, Matrix &rotation_z, Matrix &rotation_isometric)
{
    rotation_z.elements = {
        {std::cos(angle), -std::sin(angle), 0},
        {std::sin(angle), std::cos(angle), 0},
        {0, 0, 1}};

    rotation_x.elements = {
        {1, 0, 0},
        {0, std::cos(angle), std::sin(angle)},
        {0, -std::sin(angle), std::cos(angle)}};

    rotation_y.elements = {
        {std::cos(angle), 0, -std::sin(angle)},
        {0, 1, 0},
        {std::sin(angle), 0, std::cos(angle)}};

    rotation_isometric.elements = {
        {1, 0, 0},
        {0, std::cos(angle), std::sin(angle)},
        {0, -std::sin(angle), std::cos(angle)}};
}

void connect(int i, int j, const std::vector<Vector> &points)
{
    Vector a = points[i];
    Vector b = points[j];
    SDLController::render_line(a.x, a.y, b.x, b.y);
}

int main()
{
    SDLController::create_window(800, 800);
    Board board;
    board.resize(8);

    Knight black_knight;
    black_knight.tour(&board);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    std::vector<Vector> points = {
        Vector(-50, -50, -50),
        Vector(50, -50, -50),
        Vector(50, 50, -50),
        Vector(-50, 50, -50),
        Vector(-50, -50, 50),
        Vector(50, -50, 50),
        Vector(50, 50, 50),
        Vector(-50, 50, 50)};

    Matrix projection_matrix(2, 3);
    projection_matrix.elements = {{1, 0, 0},
                                  {0, 1, 0}};

    Matrix rotation_z_matrix(3, 3);
    rotation_z_matrix.elements = {
        {std::cos(angle), -std::sin(angle), 0},
        {std::sin(angle), std::cos(angle), 0},
        {0, 0, 1}};

    Matrix rotation_x_matrix(3, 3);
    rotation_x_matrix.elements = {
        {1, 0, 0},
        {0, std::cos(angle), std::sin(angle)},
        {0, -std::sin(angle), std::cos(angle)}};

    Matrix rotation_y_matrix(3, 3);
    rotation_y_matrix.elements = {
        {std::cos(angle), 0, std::sin(angle)},
        {0, 1, 0},
        {-std::sin(angle), 0, std::cos(angle)}};

    Matrix rotation_isometric(3, 3);
    rotation_isometric.elements = {
        {1, 0, 0},
        {0, std::cos(angle), std::sin(angle)},
        {0, -std::sin(angle), std::cos(angle)}};

    rotation_z_matrix.print();

    while (true)
    {
        std::vector<Vector> projected_points;

        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events();

        SDLController::set_color(255, 0, 0);
        for (const auto &point : points)
        {
            auto rotated = Matrix::dot_product(rotation_z_matrix, point);
            //rotated = Matrix::dot_product(rotation_y_matrix, rotated);
            rotated = Matrix::dot_product(rotation_x_matrix, rotated);
            auto projected = Matrix::dot_product(projection_matrix, rotated);
            auto p = projected.to_vector();
            p.translate(250, 250);
            projected_points.emplace_back(p);
            std::cout << p.x << ' ' << p.y << '\n';
        }

        for (auto i = 0; i < 4; i++)
        {
            connect(i, (i + 1) % 4, projected_points);
            connect(i + 4, ((i + 1) % 4) + 4, projected_points);
            connect(i, i + 4, projected_points);
        }

        angle += 0.03;

        std::cout << "angle: " << angle << '\n';
        update_matrices(rotation_x_matrix, rotation_y_matrix, rotation_z_matrix, rotation_isometric);

        SDLController::update_screen();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
