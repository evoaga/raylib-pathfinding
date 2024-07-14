#include "vector_math.hpp"

Vector3 Vector3Add(Vector3 v1, Vector3 v2) {
    Vector3 result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

Vector3 Vector3Subtract(Vector3 v1, Vector3 v2) {
    Vector3 result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return result;
}

Vector3 Vector3Scale(Vector3 v, float scalar) {
    Vector3 result = { v.x * scalar, v.y * scalar, v.z * scalar };
    return result;
}

float Vector3Length(const Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Vector3Normalize(Vector3 v) {
    float length = Vector3Length(v);
    if (length != 0.0f) {
        float ilength = 1.0f / length;
        v.x *= ilength;
        v.y *= ilength;
        v.z *= ilength;
    }
    return v;
}
