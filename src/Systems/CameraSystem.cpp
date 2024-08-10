#include "CameraSystem.hpp"
#include "../Components/Components.hpp"
#include "../VectorMath.hpp"
#include "raylib.h"

auto InitCamera(Camera &camera) -> void
{
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

auto CameraSystem(entt::registry &registry) -> void
{
    const float baseCameraSpeed = 0.3f;
    const int edgeThreshold = 100;

    auto playerView = registry.view<TransformComponent, Player>();
    auto cameraView = registry.view<CameraComponent>();

    playerView.each([&](auto, TransformComponent &playerTransform)
                    { cameraView.each([&](auto, CameraComponent &cameraComponent)
                                      {
            Camera& camera = cameraComponent.camera;
            cameraComponent.zoomLevel = fmax(cameraComponent.zoomLevel + GetMouseWheelMove() * -0.1f, 0.1f);

            if (cameraComponent.attached) {
                camera.target = playerTransform.position;
                camera.position = Vector3Add(playerTransform.position, { 0.0f, 10.0f * cameraComponent.zoomLevel, 10.0f * cameraComponent.zoomLevel });
            } else {
                float cameraSpeed = baseCameraSpeed * GetFrameTime() * 60.0f;
                Vector2 mousePosition = GetMousePosition();

                if (mousePosition.x <= edgeThreshold) camera.position.x -= cameraSpeed;
                if (mousePosition.x >= GetScreenWidth() - edgeThreshold) camera.position.x += cameraSpeed;
                if (mousePosition.y <= edgeThreshold) camera.position.z -= cameraSpeed;
                if (mousePosition.y >= GetScreenHeight() - edgeThreshold) camera.position.z += cameraSpeed;

                camera.target = Vector3Add(camera.position, { 0.0f, -10.0f, -10.0f });
            } }); });
}
