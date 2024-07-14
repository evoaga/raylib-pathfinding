#ifndef VECTOR_MATH_HPP
#define VECTOR_MATH_HPP

#include <cmath>
#include "raylib.h"

Vector3 Vector3Add(Vector3 v1, Vector3 v2);
Vector3 Vector3Subtract(Vector3 v1, Vector3 v2);
Vector3 Vector3Scale(Vector3 v, float scalar);
float Vector3Length(const Vector3 v);
Vector3 Vector3Normalize(Vector3 v);
Vector3 Vector3Transform(Vector3 v, Matrix mat);
Matrix MatrixRotateXYZ(Vector3 angle);
Matrix MatrixTranslate(float x, float y, float z);
Matrix MatrixMultiply(Matrix left, Matrix right);

#endif // VECTOR_MATH_HPP
