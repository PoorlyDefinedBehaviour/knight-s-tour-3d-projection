#pragma once
#include "../matrix/matrix.h"
#include <vector>
#include <array>

struct MatrixPosition
{
  int row;
  int column;
  int step_count;
};

enum class BoardState
{
  NOT_VISITED,
  VISITED
};

class Vector3D;

class Board
{
private:
  std::vector<std::pair<int, int>> moves = {std::make_pair(-2, 1),
                                            std::make_pair(-1, 2),
                                            std::make_pair(1, 2),
                                            std::make_pair(2, 1),
                                            std::make_pair(2, -1),
                                            std::make_pair(1, -2),
                                            std::make_pair(-1, -2),
                                            std::make_pair(-2, -1)};
  std::vector<MatrixPosition> path;
  Matrix<BoardState> grid;
  Matrix<int> solution;
  const int cell_size = 50;
  const int cube_size = 100;
  int knight_starting_row = 0;
  int knight_starting_column = 0;
  const int knight_path_drawing_delay = 60;
  int size = 8;
  int minimum_steps_for_knights_tour = size * size;
  int current_index_for_2d_path = 0;
  int current_index_for_3d_path = 0;

  bool is_move_valid(int row, int column) const noexcept;
  bool is_visited(int row, int column) const noexcept;
  std::pair<int, int> get_move_with_less_neighbours(int row, int column);
  bool find_path(int step_count, int row, int column);
  void reset();

public:
  Board();
  void handle_events();
  void resize(int size);
  void set_mininum_tour_steps(int steps);
  int get_minimum_tour_steps() const noexcept;
  void find_knights_path();
  int get_size() const noexcept;
  std::pair<int, int> get_board_pos_regarding_mouse();
  void draw_2d();
  void draw_3d();
  void draw_knights_path_3d();
  void draw_knights_path_2d();
  void draw_mouse_position();
};
