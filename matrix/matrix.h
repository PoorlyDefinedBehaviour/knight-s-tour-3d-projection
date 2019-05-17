#pragma once

template <typename T>
class Matrix
{
public:
  int rows;
  int columns;
  T **elements = nullptr;

  Matrix(int _rows = 0, int _columns = 0)
      : rows(_rows), columns(_columns)
  {
  }

  void resize(int rows, int columns)
  {
    if (this->elements)
    {
      for (int i = 0; i < this->rows; ++i)
        delete[] this->elements[i];
    }

    this->rows = rows;
    this->columns = columns;

    this->elements = new T *[this->rows];
    for (int i = 0; i < this->rows; ++i)
      this->elements[i] = new T[this->columns];

    this->fill([]() -> int { return -1; });
  }

  template <typename lambda>
  void fill(const lambda &func)
  {
    for (int i = 0; i < this->rows; ++i)
      for (int j = 0; j < this->columns; ++j)
        this->elements[i][j] = func();
  }
};