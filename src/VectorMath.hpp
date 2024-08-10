#pragma once

#include <cmath>
#include "raylib.h"

// Vector2 Operations
float Vector2Distance(Vector2 v1, Vector2 v2);

// Vector3 Arithmetic Operations
Vector3 Vector3Add(Vector3 v1, Vector3 v2);
Vector3 Vector3Subtract(Vector3 v1, Vector3 v2);
Vector3 Vector3Divide(Vector3 v1, Vector3 v2);
Vector3 Vector3Scale(Vector3 v, float scalar);
Vector3 Vector3Negate(Vector3 v);

// Vector3 Dot and Cross Products
float Vector3DotProduct(Vector3 v1, Vector3 v2);
Vector3 Vector3CrossProduct(Vector3 v1, Vector3 v2);

// Vector3 Distance and Length Operations
float Vector3Distance(Vector3 v1, Vector3 v2);
float Vector3Length(const Vector3 v);
Vector3 Vector3Normalize(Vector3 v);

// Vector3 Equality Check
bool Vector3Equals(const Vector3 &a, const Vector3 &b);

// Matrix Operations
Matrix MatrixRotateXYZ(Vector3 angle);
Matrix MatrixTranslate(float x, float y, float z);
Matrix MatrixMultiply(Matrix left, Matrix right);

// Vector3 Transformation
Vector3 Vector3Transform(Vector3 v, Matrix mat);
