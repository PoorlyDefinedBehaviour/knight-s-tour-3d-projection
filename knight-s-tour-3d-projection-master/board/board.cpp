#include "board.h"
#include "../sdlcontroller/sdlcontroller.h"
#include "../vector/vector.h"
#include <algorithm>

Board::Board()
{
    this->grid.resize(this->size, this->size);
}

void Board::resize(int size)
{
    this->grid.resize(size, size);

    this->size = size;
    this->reset();
}

void Board::reset()
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->grid.elements[i][j] = EMPTY;
        }
    }
}

bool Board::is_visited(int row, int column) const noexcept
{
    return this->grid.elements[row][column] != EMPTY;
}

void Board::draw_2d()
{
    /**
     * light blue = rgb(106, 137, 204)
     * red = rgb(198, 40, 40)
     * */

    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            if ((i + j) % 2 == 0)
            {
                SDLController::set_color(255, 255, 255);
            }
            else
            {
                SDLController::set_color(106, 137, 204);
            }

            SDLController::render_rectangle(SDLController::WINDOW_WIDTH / 2 + i * this->cell_size,
                                            100 + j * this->cell_size,
                                            this->cell_size,
                                            this->cell_size);
        }
    }
}

void Board::draw_3d()
{
    std::vector<Vector3D> projected_points;

    const int cube_size = 100;

    SDLController::set_color(46, 125, 50);
    for (auto i = 0; i < this->grid.rows; ++i)
    {
        for (auto j = 0; j < this->grid.columns; ++j)
        {
            for (auto point : SDLController::basic_cube_vertices)
            {
                point.x += i * cube_size;
                point.y += j * cube_size;
                auto rotated = Matrix::dot_product(SDLController::rotation_z, point);
                rotated = Matrix::dot_product(SDLController::rotation_y, point);
                rotated = Matrix::dot_product(SDLController::rotation_x, rotated);
                auto projected = Matrix::dot_product(SDLController::projection, rotated);
                auto p = projected.to_vector();
                p.translate(400, 300);
                p.multiply(0.5);
                projected_points.emplace_back(p);
            }

            SDLController::render_shape(projected_points);
            projected_points = {};
        }
    }
}

void Board::draw_knights_path_2d()
{
    SDL_Point points[64];

    for (size_t i = 0; i < this->path.size(); ++i)
    {
        points[i] = {(SDLController::WINDOW_WIDTH / 2 + this->path[i].row * this->cell_size) + cell_size / 2, 100 + (this->path[i].column * cell_size) + cell_size / 2};
    }

    static int current_index = 0;
    static int time_passed = 0;

    ++time_passed;

    if (time_passed >= this->knight_path_drawing_delay)
    {
        time_passed = 0;
        ++current_index;

        if (current_index == this->path.size())
        {
            current_index = 0;
        }
    }

    for (auto i = 0; i < current_index; ++i)
    {

        SDLController::set_color(198, 40, 40);

        auto current_cell = this->path[i];

        SDLController::render_rectangle(SDLController::WINDOW_WIDTH / 2 + current_cell.row * this->cell_size,
                                        100 + current_cell.column * this->cell_size,
                                        this->cell_size,
                                        this->cell_size);
    }

    SDLController::set_color(46, 125, 50);
    SDLController::render_lines(points, current_index);
}

void Board::draw_knights_path_3d()
{
    std::vector<Vector3D> projected_points;
    const int cube_size = 100;
    static int time_passed = 0;
    static int current_index = 0;

    if (++time_passed >= this->knight_path_drawing_delay)
    {
        time_passed = 0;

        ++current_index;
        if (current_index >= this->path.size())
            current_index = 0;
    }

    SDLController::set_color(255, 0, 0);
    for (auto i = 0; i < current_index; ++i)
    {
        for (auto point : SDLController::basic_cube_vertices)
        {
            point.x += this->path[i].row * cube_size;
            point.y += this->path[i].column * cube_size;
            point.z += 400;
            auto rotated = Matrix::dot_product(SDLController::rotation_z, point);
            rotated = Matrix::dot_product(SDLController::rotation_y, point);
            rotated = Matrix::dot_product(SDLController::rotation_x, rotated);
            auto projected = Matrix::dot_product(SDLController::projection, rotated);
            auto p = projected.to_vector();
            p.translate(400, 300);
            p.multiply(0.5);
            projected_points.emplace_back(p);
        }

        SDLController::render_shape(projected_points);
        projected_points = {};
    }
}

void Board::knight_tour()
{
    this->solution.resize(this->size, this->size);
    this->solution.fill([&]() -> int { return EMPTY; });

    /* Starting position */
    this->solution.elements[0][0] = 0.0;

    this->find_path(1, 0, 0);

    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            if (this->solution.elements[i][j] != EMPTY)
                this->path.emplace_back(MatrixPosition{i, j, this->solution.elements[i][j]});
        }
    }

    this->solution.print();

    std::sort(this->path.begin(),
              this->path.end(),
              [](const auto &lhs, const auto &rhs) -> bool {
                  return lhs.step_count < rhs.step_count;
              });
}

bool Board::find_path(int step_count, int row, int column)
{
    static int row_moves[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    static int column_moves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    if (step_count == this->size * this->size)
    {
        return true;
    }

    for (int i = 0; i < this->size; ++i)
    {
        const int next_row = row + row_moves[i];
        const int next_column = column + column_moves[i];

        if (is_move_valid(next_row, next_column))
        {
            this->solution.elements[next_row][next_column] = step_count;

            if (find_path(step_count + 1, next_row, next_column))
            {
                return true;
            }
            else
            {
                this->solution.elements[next_row][next_column] = EMPTY;
            }
        }
    }

    return false;
}

bool Board::is_move_valid(int row, int column)
{
    return row >= 0 &&
           column >= 0 &&
           row < this->size &&
           column < this->size &&
           this->solution.elements[row][column] == EMPTY;
}