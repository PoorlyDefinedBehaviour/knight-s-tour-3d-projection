#pragma once

/**
 * TODO: add vector methods later
 * */
class Vector
{
private:
public:
  Vector(float _x, float _y, float _z = 0);
  int x;
  int y;
  int z = 0;

  float get_magnitude();
  void set_magnitude(float new_magnitude);
  void multiply(float number);
  void translate(float x, float y = 0, float z = 0);
  void normalize();
};