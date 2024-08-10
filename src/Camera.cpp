#include "Camera.hpp"

Camera InitCamera()
{
    Camera camera = {0};

    camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

void HandleCameraMovement(Camera &camera, Vector3 currentPositionThetaStar, bool &cameraAttached)
{
    const float baseCameraSpeed = 0.3f;
    const int edgeThreshold = 100;
    static float zoomLevel = 1.0f; // Initial zoom level

    // Toggle camera attachment with the 'Y' key
    if (IsKeyPressed(KEY_Y))
    {
        cameraAttached = !cameraAttached;
    }

    // Zoom in and out with the mouse wheel
    zoomLevel += GetMouseWheelMove() * -0.1f;
    if (zoomLevel < 0.1f)
        zoomLevel = 0.1f; // Prevent too much zoom out

    if (cameraAttached)
    {
        camera.target = currentPositionThetaStar;
        camera.position = Vector3Add(currentPositionThetaStar, (Vector3){0.0f, 10.0f * zoomLevel, 10.0f * zoomLevel});
    }
    else
    {
        float cameraSpeed = baseCameraSpeed * GetFrameTime() * 60.0f;
        Vector2 mousePosition = GetMousePosition();

        if (mousePosition.x <= edgeThreshold)
            camera.position.x -= cameraSpeed;
        if (mousePosition.x >= GetScreenWidth() - edgeThreshold)
            camera.position.x += cameraSpeed;
        if (mousePosition.y <= edgeThreshold)
            camera.position.z -= cameraSpeed;
        if (mousePosition.y >= GetScreenHeight() - edgeThreshold)
            camera.position.z += cameraSpeed;

        camera.target = Vector3Add(camera.position, (Vector3){0.0f, -10.0f * zoomLevel, -10.0f * zoomLevel});
    }
}
