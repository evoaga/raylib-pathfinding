#include "VectorMath.hpp"

// Vector2 Operations
auto Vector2Distance(Vector2 v1, Vector2 v2) -> float
{
    float result = sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
    return result;
}

// Vector3 Arithmetic Operations
auto Vector3Add(Vector3 v1, Vector3 v2) -> Vector3
{
    Vector3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}

auto Vector3Subtract(Vector3 v1, Vector3 v2) -> Vector3
{
    Vector3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

auto Vector3Divide(Vector3 v1, Vector3 v2) -> Vector3
{
    Vector3 result = {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
    return result;
}

auto Vector3Scale(Vector3 v, float scalar) -> Vector3
{
    Vector3 result = {v.x * scalar, v.y * scalar, v.z * scalar};
    return result;
}

auto Vector3Negate(Vector3 v) -> Vector3
{
    Vector3 result = {-v.x, -v.y, -v.z};
    return result;
}

// Vector3 Dot and Cross Products
auto Vector3DotProduct(Vector3 v1, Vector3 v2) -> float
{
    float result = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    return result;
}

auto Vector3CrossProduct(Vector3 v1, Vector3 v2) -> Vector3
{
    Vector3 result = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
    return result;
}

// Vector3 Distance and Length Operations
auto Vector3Distance(Vector3 v1, Vector3 v2) -> float
{
    float result = 0.0f;
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    result = sqrtf(dx * dx + dy * dy + dz * dz);
    return result;
}

auto Vector3Length(const Vector3 v) -> float
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

auto Vector3Normalize(Vector3 v) -> Vector3
{
    float length = Vector3Length(v);
    if (length != 0.0f)
    {
        float ilength = 1.0f / length;
        v.x *= ilength;
        v.y *= ilength;
        v.z *= ilength;
    }
    return v;
}

// Vector3 Equality Check
auto Vector3Equals(const Vector3 &a, const Vector3 &b) -> bool
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// Matrix Operations
auto MatrixRotateXYZ(Vector3 angle) -> Matrix
{
    Matrix result = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f}; // MatrixIdentity()

    float cosz = cosf(-angle.z);
    float sinz = sinf(-angle.z);
    float cosy = cosf(-angle.y);
    float siny = sinf(-angle.y);
    float cosx = cosf(-angle.x);
    float sinx = sinf(-angle.x);

    result.m0 = cosz * cosy;
    result.m1 = (cosz * siny * sinx) - (sinz * cosx);
    result.m2 = (cosz * siny * cosx) + (sinz * sinx);

    result.m4 = sinz * cosy;
    result.m5 = (sinz * siny * sinx) + (cosz * cosx);
    result.m6 = (sinz * siny * cosx) - (cosz * sinx);

    result.m8 = -siny;
    result.m9 = cosy * sinx;
    result.m10 = cosy * cosx;

    return result;
}

auto MatrixTranslate(float x, float y, float z) -> Matrix
{
    Matrix result = {1.0f, 0.0f, 0.0f, x,
                     0.0f, 1.0f, 0.0f, y,
                     0.0f, 0.0f, 1.0f, z,
                     0.0f, 0.0f, 0.0f, 1.0f};

    return result;
}

auto MatrixMultiply(Matrix left, Matrix right) -> Matrix
{
    Matrix result;

    result.m0 = left.m0 * right.m0 + left.m1 * right.m4 + left.m2 * right.m8 + left.m3 * right.m12;
    result.m1 = left.m0 * right.m1 + left.m1 * right.m5 + left.m2 * right.m9 + left.m3 * right.m13;
    result.m2 = left.m0 * right.m2 + left.m1 * right.m6 + left.m2 * right.m10 + left.m3 * right.m14;
    result.m3 = left.m0 * right.m3 + left.m1 * right.m7 + left.m2 * right.m11 + left.m3 * right.m15;
    result.m4 = left.m4 * right.m0 + left.m5 * right.m4 + left.m6 * right.m8 + left.m7 * right.m12;
    result.m5 = left.m4 * right.m1 + left.m5 * right.m5 + left.m6 * right.m9 + left.m7 * right.m13;
    result.m6 = left.m4 * right.m2 + left.m5 * right.m6 + left.m6 * right.m10 + left.m7 * right.m14;
    result.m7 = left.m4 * right.m3 + left.m5 * right.m7 + left.m6 * right.m11 + left.m7 * right.m15;
    result.m8 = left.m8 * right.m0 + left.m9 * right.m4 + left.m10 * right.m8 + left.m11 * right.m12;
    result.m9 = left.m8 * right.m1 + left.m9 * right.m5 + left.m10 * right.m9 + left.m11 * right.m13;
    result.m10 = left.m8 * right.m2 + left.m9 * right.m6 + left.m10 * right.m10 + left.m11 * right.m14;
    result.m11 = left.m8 * right.m3 + left.m9 * right.m7 + left.m10 * right.m11 + left.m11 * right.m15;
    result.m12 = left.m12 * right.m0 + left.m13 * right.m4 + left.m14 * right.m8 + left.m15 * right.m12;
    result.m13 = left.m12 * right.m1 + left.m13 * right.m5 + left.m14 * right.m9 + left.m15 * right.m13;
    result.m14 = left.m12 * right.m2 + left.m13 * right.m6 + left.m14 * right.m10 + left.m15 * right.m14;
    result.m15 = left.m12 * right.m3 + left.m13 * right.m7 + left.m14 * right.m11 + left.m15 * right.m15;

    return result;
}

// Vector3 Transformation
auto Vector3Transform(Vector3 v, Matrix mat) -> Vector3
{
    Vector3 result;

    float x = v.x;
    float y = v.y;
    float z = v.z;

    result.x = mat.m0 * x + mat.m4 * y + mat.m8 * z + mat.m12;
    result.y = mat.m1 * x + mat.m5 * y + mat.m9 * z + mat.m13;
    result.z = mat.m2 * x + mat.m6 * y + mat.m10 * z + mat.m14;

    return result;
}
