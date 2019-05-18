#include "matrix.h"

Matrix::Matrix(int _rows, int _columns)
    : rows(_rows), columns(_columns)
{
  this->resize(this->rows, this->columns);
}

void Matrix::print()
{
  std::cout << this->rows << " x " << this->columns << '\n';
  for (auto i = 0; i < this->rows; ++i)
  {
    for (auto j = 0; j < this->columns; ++j)
    {
      std::cout << this->elements[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void Matrix::resize(int rows, int columns)
{
  this->elements = std::vector<std::vector<double>>(rows, std::vector<double>(columns));

  this->rows = rows;
  this->columns = columns;
}

Matrix Matrix::dot_product(const Matrix &a, const Matrix &b)
{
  Matrix result(a.rows, b.columns);

  for (auto i = 0; i < a.rows; ++i)
  {
    for (auto j = 0; j < b.columns; ++j)
    {

      auto sum = 0.0;
      for (auto k = 0; k < a.columns; ++k)
      {
        sum += a.elements[i][k] * b.elements[k][j];
      }
      result.elements[i][j] = sum;
    }
  }

  return result;
}

Matrix Matrix::dot_product(const Matrix &a, const Vector &b)
{
  Matrix new_matrix(3, 1);
  new_matrix.elements[0][0] = b.x;
  new_matrix.elements[1][0] = b.y;
  new_matrix.elements[2][0] = b.z;

  return dot_product(a, new_matrix);
}

Matrix Matrix::dot_product(const Vector &other)
{
  Matrix new_matrix(3, 1);
  new_matrix.elements[0][0] = other.x;
  new_matrix.elements[1][0] = other.y;
  new_matrix.elements[2][0] = other.z;

  return this->dot_product(new_matrix);
}

Matrix Matrix::add_scalar(int number)
{
  Matrix result;
  result.resize(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] + number;

  return result;
}

Matrix Matrix::subtract_scalar(int number)
{
  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] - number;

  return result;
}

Matrix Matrix::multiply_scalar(int number)
{
  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] * number;

  return result;
}

Matrix Matrix::element_wise_multiply(const Matrix &other)
{
  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][i] = this->elements[i][j] * other.elements[i][j];

  return result;
}

Matrix Matrix::subtract(const Matrix &other)
{
  if (this->rows != other.rows || this->columns || other.columns)
    throw std::length_error("Matrix B must be the same size as Matrix B");

  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] - other.elements[i][j];

  return result;
}

Matrix Matrix::dot_product(const Matrix &other)
{
  if (this->columns != other.rows)
    throw std::length_error("Matrix A columns must be the same as Matrix B rows.");

  Matrix result(this->rows, other.columns);

  for (auto i = 0; i < result.rows; i++)
  {
    for (auto j = 0; j < result.columns; j++)
    {
      auto sum = this->elements[0][0] - this->elements[0][0];
      for (auto k = 0; k < this->columns; k++)
      {
        sum += this->elements[j][k] * other.elements[k][i];
      }
      result.elements[i][j] = sum;
    }
  }

  return result;
}

Matrix Matrix::transpose()
{
  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < result.rows; i++)
  {
    for (auto j = 0; j < result.columns; j++)
    {
      result.elements[j][i] = this->elements[i][j];
    }
  }
  return result;
}

Vector Matrix::to_vector()
{
  return Vector(this->elements[0][0],
                this->elements[1][0],
                this->rows > 2 ? this->elements[2][0] : 0);
}

std::vector<double> Matrix::to_array()
{
  std::vector<double> result;

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.emplace_back(this->elements[i][j]);

  return result;
}