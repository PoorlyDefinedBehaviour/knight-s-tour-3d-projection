#include "matrix.h"

Matrix::Matrix(int _rows, int _columns)
    : rows(_rows), columns(_columns)
{
  this->resize(this->rows, this->columns);
}

Matrix Matrix::operator*(const Matrix &other)
{
  Matrix result(rows, other.columns);

  for (auto i = 0; i < rows; ++i)
  {
    for (auto j = 0; j < other.columns; ++j)
    {

      auto sum = 0.0;
      for (auto k = 0; k < columns; ++k)
      {
        sum += elements[i][k] * other.elements[k][j];
      }
      result.elements[i][j] = sum;
    }
  }

  return result;
}

Matrix Matrix::operator*(const Vector3D &other)
{
  Matrix new_matrix(3, 1);
  new_matrix.elements[0][0] = other.x;
  new_matrix.elements[1][0] = other.y;
  new_matrix.elements[2][0] = other.z;

  return *this * new_matrix;
}

Matrix Matrix::operator*(int number)
{
  Matrix result(rows, columns);

  for (auto i = 0; i < rows; ++i)
    for (auto j = 0; j < columns; ++j)
      result.elements[i][j] = elements[i][j] * number;

  return result;
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

Matrix Matrix::operator+(const Matrix &other)
{
  Matrix result;
  result.resize(rows, columns);

  for (auto i = 0; i < rows; ++i)
    for (auto j = 0; j < columns; ++j)
      result.elements[i][j] = elements[i][j] + other.elements[i][j];

  return result;
}

Matrix Matrix::operator+(int number)
{
  Matrix result;
  result.resize(rows, columns);

  for (auto i = 0; i < rows; ++i)
    for (auto j = 0; j < columns; ++j)
      result.elements[i][j] = elements[i][j] + number;

  return result;
}

Matrix Matrix::operator-(const Matrix &other)
{
  Matrix result;
  result.resize(rows, columns);

  for (auto i = 0; i < rows; ++i)
    for (auto j = 0; j < columns; ++j)
      result.elements[i][j] = elements[i][j] - other.elements[i][j];

  return result;
}

Matrix Matrix::operator-(int number)
{
  Matrix result;
  result.resize(rows, columns);

  for (auto i = 0; i < rows; ++i)
    for (auto j = 0; j < columns; ++j)
      result.elements[i][j] = elements[i][j] - number;

  return result;
}

Matrix Matrix::element_wise_add(const Matrix &other)
{
  if (this->rows != other.rows || this->columns || other.columns)
    throw std::length_error("Matrix B must be the same size as Matrix B");

  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] + other.elements[i][j];

  return result;
}

Matrix Matrix::element_wise_subtract(const Matrix &other)
{
  if (this->rows != other.rows || this->columns || other.columns)
    throw std::length_error("Matrix B must be the same size as Matrix B");

  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][j] = this->elements[i][j] - other.elements[i][j];

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

Matrix Matrix::element_wise_divide(const Matrix &other)
{
  Matrix result(this->rows, this->columns);

  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->columns; ++j)
      result.elements[i][i] = this->elements[i][j] / other.elements[i][j];

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

Vector3D Matrix::to_vector()
{
  return Vector3D(this->elements[0][0],
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
