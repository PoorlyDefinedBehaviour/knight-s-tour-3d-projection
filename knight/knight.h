#pragma once
#include "../matrix/matrix.h"

#include <vector>

class Board;

struct MatrixPosition
{
  int row;
  int column;
  int step_count;
};

class Knight
{
private:
  struct MoveSet
  {
    int row_moves[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int column_moves[8] = {1, 2, 2, 1, -1, -2, -2, -1};
  };

  MoveSet moves;
  Matrix solution;
  std::vector<MatrixPosition> path;
  Board *current_board;

  bool find_path(int step_count, int row, int column);
  bool is_move_valid(int row, int column);

public:
  void tour(Board *board);
  void show_path();
};