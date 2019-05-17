#include "knight.h"
#include "../board/board.h"

#include <algorithm>
#include <iostream>

void Knight::tour(Board *board)
{
  this->current_board = board;
  this->solution.resize(this->current_board->get_size(),
                        this->current_board->get_size());
  this->solution.elements[0][0] = 0;

  if (!this->find_path(1, 0, 0))
  {
    std::cout << "No solution found..." << '\n';
  }
  else
  {
    for (int i = 0; i < this->current_board->get_size(); ++i)
    {
      for (int j = 0; j < this->current_board->get_size(); ++j)
      {
        this->path.push_back({i, j, this->solution.elements[i][j]});
      }
    }

    std::sort(this->path.begin(),
              this->path.end(),
              [](const auto &lhs, const auto &rhs) -> bool {
                return lhs.step_count < rhs.step_count;
              });
  }
}

bool Knight::find_path(int step_count, int row, int column)
{
  static const int board_size = this->current_board->get_size();

  if (step_count == board_size * board_size)
  {
    return true;
  }

  for (int i = 0; i < board_size; ++i)
  {
    int next_row = row + moves.row_moves[i];
    int next_column = column + moves.column_moves[i];

    if (is_move_valid(next_row, next_column))
    {
      this->solution.elements[next_row][next_column] = step_count;

      if (find_path(step_count + 1, next_row, next_column))
      {
        // std::cout << row << ", " << column << " step: " << step_count << '\n';
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

bool Knight::is_move_valid(int row, int column)
{
  static const int board_size = this->current_board->get_size();

  return row >= 0 &&
         column >= 0 &&
         row < board_size &&
         column < board_size &&
         this->solution.elements[row][column] == -1;
}

void Knight::show_path()
{
  const int delay = 30;
  static int current_index = 0;
  static int time_passed = 0;

  ++time_passed;

  if (time_passed >= delay)
  {
    this->current_board->visit(this->path[current_index].row,
                               this->path[current_index].column);

    time_passed = 0;
    ++current_index;
  }
}