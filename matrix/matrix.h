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
  Matrix operator*(const Matrix &other);
  Matrix operator*(const Vector3D &other);
  Matrix operator*(int number);
  Matrix operator+(const Matrix &other);
  Matrix operator+(int number);
  Matrix operator-(const Matrix &other);
  Matrix operator-(int number);
  Matrix element_wise_add(const Matrix &other);
  Matrix element_wise_subtract(const Matrix &other);
  Matrix element_wise_multiply(const Matrix &other);
  Matrix element_wise_divide(const Matrix &other);

  void print();
  void resize(int rows, int columns);
  Matrix transpose();
  Vector3D to_vector();
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
