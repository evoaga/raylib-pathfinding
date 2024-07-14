#include "utils.hpp"

// Function to convert 2D mouse position to 3D point on ground plane
Vector3 GetMousePosition3D(Camera3D camera) {
    Vector2 mousePosition = GetMousePosition();
    Ray ray = GetMouseRay(mousePosition, camera);

    // Calculate the point on the ground plane (y = 0)
    float t = -ray.position.y / ray.direction.y;
    Vector3 mousePosition3D = Vector3Add(ray.position, Vector3Scale(ray.direction, t));

    return mousePosition3D;
}

// Function to check if a line segment intersects with a bounding box
bool CheckCollisionSegmentBox(Vector3 start, Vector3 end, BoundingBox box) {
    Vector3 d = Vector3Subtract(end, start);

    float tmin = (box.min.x - start.x) / d.x;
    float tmax = (box.max.x - start.x) / d.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (box.min.z - start.z) / d.z;
    float tymax = (box.max.z - start.z) / d.z;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    return tmax >= 0.0f && tmin <= 1.0f;
}
