#include <iostream>
#include <vector>
#include <cmath>
#include "sdlcontroller/sdlcontroller.h"
#include "board/board.h"
#include "knight/knight.h"
#include "vector/vector.h"

void update_matrices(Matrix &rotation_x, Matrix &rotation_y, Matrix &rotation_z, Matrix &rotation_isometric, float angle)
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

    float angle = 0;

    std::vector<std::vector<Vector>> all_points;

    std::vector<Vector> points = {
        Vector(-50, -50, -50),
        Vector(50, -50, -50),
        Vector(50, 50, -50),
        Vector(-50, 50, -50),
        Vector(-50, -50, 50),
        Vector(50, -50, 50),
        Vector(50, 50, 50),
        Vector(-50, 50, 50)};

    std::vector<Vector> points2 = {
        Vector(-150, -150, -150),
        Vector(150, -150, -150),
        Vector(150, 150, -150),
        Vector(-150, 150, -150),
        Vector(-150, -150, 150),
        Vector(150, -150, 150),
        Vector(150, 150, 150),
        Vector(-150, 150, 150)};

    all_points.emplace_back(points);
    all_points.emplace_back(points2);

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

    while (true)
    {
        frameStart = SDL_GetTicks();

        SDLController::clear_screen();
        SDLController::handle_events(points);

        SDLController::set_color(255, 0, 0);
        //for (const auto &points_vector : all_points)
        //{
        std::vector<Vector> projected_points;
        update_matrices(rotation_x_matrix, rotation_y_matrix, rotation_z_matrix, rotation_isometric, 45);
        for (const auto &point : points2)
        {
            auto rotated = Matrix::dot_product(rotation_z_matrix, point);
            //rotated = Matrix::dot_product(rotation_y_matrix, rotated);
            rotated = Matrix::dot_product(rotation_x_matrix, rotated);
            auto projected = Matrix::dot_product(projection_matrix, rotated);
            auto p = projected.to_vector();
            p.translate(250, 250);
            projected_points.emplace_back(p);
        }
        SDLController::render_shape(projected_points);

        projected_points = {};

        update_matrices(rotation_x_matrix, rotation_y_matrix, rotation_z_matrix, rotation_isometric, 45);
        for (const auto &point : points)
        {
            auto rotated = Matrix::dot_product(rotation_z_matrix, point);
            //rotated = Matrix::dot_product(rotation_y_matrix, rotated);
            rotated = Matrix::dot_product(rotation_x_matrix, rotated);
            auto projected = Matrix::dot_product(projection_matrix, rotated);
            auto p = projected.to_vector();
            p.translate(250, 250);
            projected_points.emplace_back(p);
        }
        SDLController::render_shape(projected_points);
        // }

        angle += 0.03;

        SDLController::update_screen();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
