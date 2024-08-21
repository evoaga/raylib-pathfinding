#pragma once

#include <cmath>
#include "raylib.h"

// Vector2 Operations
auto Vector2Distance(Vector2 v1, Vector2 v2) -> float;

// Vector3 Arithmetic Operations
auto Vector3Add(Vector3 v1, Vector3 v2) -> Vector3;
auto Vector3Subtract(Vector3 v1, Vector3 v2) -> Vector3;
auto Vector3Divide(Vector3 v1, Vector3 v2) -> Vector3;
auto Vector3Scale(Vector3 v, float scalar) -> Vector3;
auto Vector3Negate(Vector3 v) -> Vector3;

// Vector3 Dot and Cross Products
auto Vector3DotProduct(Vector3 v1, Vector3 v2) -> float;
auto Vector3CrossProduct(Vector3 v1, Vector3 v2) -> Vector3;

// Vector3 Distance and Length Operations
auto Vector3Distance(Vector3 v1, Vector3 v2) -> float;
auto Vector3Length(Vector3 v) -> float;
auto Vector3Normalize(Vector3 v) -> Vector3;

// Vector3 Equality Check
auto Vector3Equals(const Vector3 &a, const Vector3 &b) -> bool;

// Matrix Operations
auto MatrixRotateXYZ(Vector3 angle) -> Matrix;
auto MatrixTranslate(float x, float y, float z) -> Matrix;
auto MatrixMultiply(Matrix left, Matrix right) -> Matrix;

// Vector3 Transformation
auto Vector3Transform(Vector3 v, Matrix mat) -> Vector3;