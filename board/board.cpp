#include "board.h"
#include "../sdlcontroller/sdlcontroller.h"
#include "../vector/vector.h"
#include <algorithm>

Board::Board()
{
  this->grid.resize(this->size, this->size);
}

void Board::handle_events()
{
  if (SDLController::event_handler.type == SDL_MOUSEBUTTONDOWN && SDLController::event_handler.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
  {
    SDL_PollEvent(&SDLController::event_handler);
    SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
    SDL_PumpEvents();

    auto position = this->get_board_pos_regarding_mouse();
    const int &row = position.first;
    const int &column = position.second;

    if (row != -1 && column != -1)
    {
      this->knight_starting_row = row;
      this->knight_starting_column = column;
    }
  }
}

void Board::resize(int size)
{
  if (size < 3 || size > 8 || this->size == size)
    return;

  this->size = size;
  this->minimum_steps_for_knights_tour = this->size * this->size;
  this->reset();
}

void Board::set_mininum_tour_steps(int steps)
{
  if (steps == 0 || steps > this->size * this->size)
    return;

  this->minimum_steps_for_knights_tour = steps;
  this->reset();
}

int Board::get_minimum_tour_steps() const noexcept
{
  return this->minimum_steps_for_knights_tour;
}

void Board::reset()
{
  this->grid.resize(size, size);
  this->grid.fill([&]() { return BoardState::NOT_VISITED; });
  this->path.clear();
  this->current_index_for_2d_path = this->current_index_for_3d_path = 0;
  this->knight_starting_row = this->knight_starting_column = 0;
}

bool Board::is_visited(int row, int column) const noexcept
{
  return this->grid.elements[row][column] != BoardState::NOT_VISITED;
}

void Board::draw_2d()
{
  for (auto i = 0; i < this->size; ++i)
  {
    for (auto j = 0; j < this->size; ++j)
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

  SDLController::set_color(46, 125, 50);
  for (auto i = 0; i < this->grid.rows; ++i)
  {
    for (auto j = 0; j < this->grid.columns; ++j)
    {
      for (auto point : SDLController::basic_cube_vertices)
      {
        point.x += i * cube_size;
        point.y += j * cube_size;
        auto rotated = SDLController::rotation_z * point;
        rotated = SDLController::rotation_y * rotated;
        rotated = SDLController::rotation_x * rotated;
        auto projected = SDLController::projection * rotated;
        auto p = projected.to_vector3d();
        p.translate(400, 300, 0);
        p.multiply(0.5);
        projected_points.emplace_back(p);
      }

      SDLController::render_shape(projected_points);
      projected_points.clear();
    }
  }
}

void Board::draw_knights_path_2d()
{
  SDL_Point points[64];
  static int time_passed = 0;

  SDLController::set_color(255, 0, 0);
  SDLController::render_rectangle(SDLController::WINDOW_HALF_WIDTH + this->knight_starting_row * this->cell_size,
                                  100 + this->knight_starting_column * this->cell_size,
                                  this->cell_size, this->cell_size);

  for (size_t i = 0; i < this->path.size(); ++i)
  {
    points[i] = {(SDLController::WINDOW_WIDTH / 2 + this->path[i].row * this->cell_size) + cell_size / 2,
                 100 + (this->path[i].column * cell_size) + cell_size / 2};
  }

  if (++time_passed >= this->knight_path_drawing_delay)
  {
    time_passed = 0;

    if (++current_index_for_2d_path >= this->path.size())
    {
      current_index_for_2d_path = 0;
      this->path.clear();
    }
  }

  for (auto i = 0; i < current_index_for_2d_path; ++i)
  {
    SDLController::set_color(198, 40, 40);

    auto current_cell = this->path[i];

    SDLController::render_rectangle(SDLController::WINDOW_WIDTH / 2 + current_cell.row * this->cell_size,
                                    100 + current_cell.column * this->cell_size,
                                    this->cell_size,
                                    this->cell_size);
  }

  SDLController::set_color(46, 125, 50);
  SDLController::render_lines(points, current_index_for_2d_path);
}

void Board::draw_knights_path_3d()
{
  std::vector<Vector3D> projected_points;
  static int time_passed = 0;

  SDLController::set_color(255, 0, 0);
  for (auto point : SDLController::basic_cube_vertices)
  {
    point.x += this->knight_starting_row * cube_size;
    point.y += this->knight_starting_column * cube_size;
    point.z += 400;
    auto rotated = SDLController::rotation_z * point;
    rotated = SDLController::rotation_y * rotated;
    rotated = SDLController::rotation_x * rotated;
    auto projected = SDLController::projection * rotated;
    auto p = projected.to_vector3d();
    p.translate(400, 300, 0);
    p.multiply(0.5);
    projected_points.emplace_back(p);
  }

  SDLController::render_shape(projected_points);
  projected_points.clear();

  if (++time_passed >= this->knight_path_drawing_delay)
  {
    time_passed = 0;

    if (++current_index_for_3d_path >= this->path.size())
      current_index_for_3d_path = 0;
  }

  SDLController::set_color(255, 0, 0);
  for (auto i = 0; i < current_index_for_3d_path; ++i)
  {
    for (auto point : SDLController::basic_cube_vertices)
    {
      point.x += this->path[i].row * cube_size;
      point.y += this->path[i].column * cube_size;
      point.z += 400;
      auto rotated = SDLController::rotation_z * point;
      rotated = SDLController::rotation_y * rotated;
      rotated = SDLController::rotation_x * rotated;
      auto projected = SDLController::projection * rotated;
      auto p = projected.to_vector3d();
      p.translate(400, 300, 0);
      p.multiply(0.5);
      projected_points.emplace_back(p);
    }

    SDLController::render_shape(projected_points);
    projected_points.clear();
  }
}

void Board::draw_mouse_position()
{
  auto position = this->get_board_pos_regarding_mouse();

  if (position.first == -1 || position.second == -1)
    return;

  const int &row = position.first;
  const int &column = position.second;

  SDLController::render_rectangle(SDLController::WINDOW_HALF_WIDTH + row * this->cell_size,
                                  100 + column * this->cell_size,
                                  this->cell_size,
                                  this->cell_size);
}

void Board::find_knights_path()
{
  this->solution.resize(this->size, this->size);
  this->solution.fill([&]() { return -1; });

  std::cout << "Searching..." << '\n';
  std::cout << "Minimum steps: " << this->minimum_steps_for_knights_tour << " -> " << (!this->find_path(1, this->knight_starting_row, this->knight_starting_column) ? "No solution found..." : "Solution found!") << '\n';

  for (int i = 0; i < this->size; ++i)
  {
    for (int j = 0; j < this->size; ++j)
    {
      if (this->solution.elements[i][j] != -1)
        this->path.emplace_back(MatrixPosition{i, j, this->solution.elements[i][j]});
    }
  }

  std::sort(this->path.begin(),
            this->path.end(),
            [](const auto &lhs, const auto &rhs) -> bool {
              return lhs.step_count < rhs.step_count;
            });
}

bool Board::find_path(int step_count, int row, int column)
{
  if (step_count == this->minimum_steps_for_knights_tour)
  {
    return true;
  }

  for (const auto &move : this->moves)
  {
    const int next_row = row + move.first;
    const int next_column = column + move.second;

    if (is_move_valid(next_row, next_column))
    {
      this->solution.elements[next_row][next_column] = step_count;

      if (find_path(step_count + 1, next_row, next_column))
      {
        return true;
      }
      else
      {
        this->solution.elements[next_row][next_column] = -1;
      }
    }
  }

  return false;
}

bool Board::is_move_valid(int row, int column) const noexcept
{
  return row >= 0 &&
         column >= 0 &&
         row < this->size &&
         column < this->size &&
         this->solution.elements[row][column] == -1;
}

int Board::get_size() const noexcept
{
  return this->size;
}

std::pair<int, int> Board::get_board_pos_regarding_mouse()
{
  auto mouse_pos = SDLController::get_mouse_position();
  const int &x = mouse_pos.first;
  const int &y = mouse_pos.second;

  if (x < SDLController::WINDOW_HALF_WIDTH || y < 100 ||
      x > (SDLController::WINDOW_HALF_WIDTH + this->size * this->cell_size) || y > (100 + this->size * this->cell_size))
  {
    return {-1, -1};
  }

  const int row = (x - SDLController::WINDOW_HALF_WIDTH) / this->cell_size;
  const int column = (y - 100) / this->cell_size;

  return std::make_pair(row, column);
}
