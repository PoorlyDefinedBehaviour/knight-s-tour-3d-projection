#pragma once

#include "../vector/vector.h"
#include <stdexcept>
#include <vector>
#include <iostream>

class Matrix
{
public:
  int rows;
  int columns;
  std::vector<std::vector<double>> elements;

  Matrix(int _rows = 0, int _columns = 0);

  void print();
  void resize(int rows, int columns);
  static Matrix dot_product(const Matrix &a, const Matrix &b);
  static Matrix dot_product(const Matrix &a, const Vector &b);
  Matrix add_scalar(int number);
  Matrix subtract_scalar(int number);
  Matrix multiply_scalar(int number);
  Matrix element_wise_multiply(const Matrix &other);
  Matrix subtract(const Matrix &other);
  Matrix dot_product(const Matrix &other);
  Matrix dot_product(const Vector &other);
  Matrix transpose();
  Vector to_vector();
  std::vector<double> to_array();

  template <typename lambda>
  Matrix map(const lambda &func)
  {
    Matrix result(this->rows, this->columns);

    for (auto i = 0; i < result.rows; i++)
    {
      for (auto j = 0; j < result.columns; j++)
      {
        result.elements[i][j] = func(this->elements[i][j]);
      }
    }
    return result;
  }

  template <typename lambda>
  void fill(const lambda &func)
  {
    for (int i = 0; i < this->rows; ++i)
      for (int j = 0; j < this->columns; ++j)
        this->elements[i][j] = func();
  }
};