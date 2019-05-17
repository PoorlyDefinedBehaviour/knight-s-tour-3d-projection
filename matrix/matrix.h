#pragma once

#include <vector>

template <typename T>
class Matrix
{
public:
  int rows;
  int columns;
  std::vector<std::vector<T>> elements;

  Matrix(int _rows = 0, int _columns = 0)
      : rows(_rows), columns(_columns)
  {
    this->resize(this->rows, this->columns);
  }

  void resize(int rows, int columns)
  {
    this->elements = std::vector<std::vector<T>>(rows, std::vector<T>(columns));

    this->rows = rows;
    this->columns = columns;
  }

  template <typename lambda>
  void fill(const lambda &func)
  {
    for (int i = 0; i < this->rows; ++i)
      for (int j = 0; j < this->columns; ++j)
        this->elements[i][j] = func();
  }
};