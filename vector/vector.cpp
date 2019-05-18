#include "vector.h"
#include <cmath>

Vector::Vector(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
{
}

float Vector::get_magnitude()
{
    return std::sqrt((x * x) + (y * y) + (z * z));
}

void Vector::set_magnitude(float new_magnitude)
{
    this->x = this->x * new_magnitude / this->get_magnitude();
    this->y = this->y * new_magnitude / this->get_magnitude();
    this->z = this->z * new_magnitude / this->get_magnitude();
}

void Vector::multiply(float number)
{
    this->x *= number;
    this->y *= number;
    this->z *= number;
}

void Vector::translate(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}

void Vector::normalize()
{
    this->multiply(1 / this->get_magnitude());
}