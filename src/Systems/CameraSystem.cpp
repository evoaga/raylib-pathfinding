#include <cmath>

#include "CameraSystem.hpp"

#include "../Components/Components.hpp"
#include "../VectorMath.hpp"
#include "entt/entity/fwd.hpp"
#include "raylib.h"

auto InitCamera(Camera &camera) -> void
{
    camera.position = {0.0F, 10.0F, 10.0F};
    camera.target = {0.0F, 0.0F, 0.0F};
    camera.up = {0.0F, 1.0F, 0.0F};
    camera.fovy = 45.0F;
    camera.projection = CAMERA_PERSPECTIVE;
}

auto CameraSystem(entt::registry &registry) -> void
{
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    const float baseCameraSpeed = 0.3F;
    const int edgeThreshold = 100;

    auto playerView = registry.view<TransformComponent, Player>();
    auto cameraView = registry.view<CameraComponent>();

    playerView.each(
        [&](auto, TransformComponent &playerTransform)
        {
            cameraView.each(
                [&](auto, CameraComponent &cameraComponent)
                {
                    Camera &camera = cameraComponent.camera;
                    cameraComponent.zoomLevel =
                        fmax(cameraComponent.zoomLevel + GetMouseWheelMove() * -0.1F, 0.1F);

                    if (cameraComponent.attached) {
                        camera.target = playerTransform.position;
                        camera.position = Vector3Add(playerTransform.position,
                                                     {0.0F,
                                                      10.0F * cameraComponent.zoomLevel,
                                                      10.0F * cameraComponent.zoomLevel});
                    } else {
                        float const cameraSpeed = baseCameraSpeed * GetFrameTime() * 60.0F;
                        Vector2 const mousePosition = GetMousePosition();

                        if (mousePosition.x <= edgeThreshold) {
                            camera.position.x -= cameraSpeed;
                        }
                        if (mousePosition.x >= screenWidth - edgeThreshold) {
                            camera.position.x += cameraSpeed;
                        }
                        if (mousePosition.y <= edgeThreshold) {
                            camera.position.z -= cameraSpeed;
                        }
                        if (mousePosition.y >= screenHeight - edgeThreshold) {
                            camera.position.z += cameraSpeed;
                        }

                        camera.target = Vector3Add(camera.position, {0.0F, -10.0F, -10.0F});
                    }
                });
        });
}
