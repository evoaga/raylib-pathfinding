#include "Scene.hpp"
#include "Obstacles.hpp"
#include "raylib.h"

void DrawHealthBarAbovePlayer(const Player& player, const Camera& camera) {
    Vector3 playerPos = player.getPosition();
    Vector2 screenPos = GetWorldToScreen(playerPos, camera);
    float healthPercentage = static_cast<float>(player.getHealth()) / 100.0f;

    int barWidth = 50;
    int barHeight = 10;
    int barX = static_cast<int>(screenPos.x) - barWidth / 2;
    int barY = static_cast<int>(screenPos.y) - 40;

    // Health bar background
    DrawRectangle(barX, barY, barWidth, barHeight, GRAY);

    // Health bar foreground
    DrawRectangle(barX, barY, static_cast<int>(barWidth * healthPercentage), barHeight, RED);

    // Health text
    DrawText(TextFormat("%d / 100", player.getHealth()), barX, barY - 10, 10, BLACK);
}

void DrawHealthBar(const Player& player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float healthPercentage = static_cast<float>(player.getHealth()) / 100.0f;

    // Health bar size
    int barWidth = 300; // Adjust the width to your preference
    int barHeight = 20;

    // Health bar position (centered)
    int barX = (screenWidth - barWidth) / 2;
    int barY = screenHeight - 50; // Position it slightly above the bottom

    // Draw the border of the health bar
    DrawRectangleLines(barX, barY, barWidth, barHeight, BLACK);

    // Draw the background of the health bar
    DrawRectangle(barX + 1, barY + 1, barWidth - 2, barHeight - 2, GRAY);

    // Draw the health foreground
    int healthBarWidth = static_cast<int>((barWidth - 2) * healthPercentage);
    DrawRectangle(barX + 1, barY + 1, healthBarWidth, barHeight - 2, RED);

    // Draw the health text (centered above the health bar)
    DrawText(TextFormat("Health: %d", player.getHealth()), barX + (barWidth / 2) - MeasureText(TextFormat("Health: %d", player.getHealth()), 20) / 2, barY - 25, 20, BLACK);
}

void DrawUI() {
    DrawFPS(10, 10);
    DrawText("Right-click to set goal point and start moving", 10, 40, 20, DARKGRAY);
    DrawText("Press R to reset obstacles", 10, 70, 20, DARKGRAY);
}

void DrawScene(const NavMesh& mesh, const std::vector<Polygon>& polygons, const std::vector<GameObject>& obstacles, float obstacleSize, const Player& player, bool goalSet, const Point& goal, const std::vector<Point>& pathThetaStar, const Camera& camera) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawCube((Vector3){5.0f, -0.1f, 5.0f}, 10.0f, 0.2f, 10.0f, LIGHTGRAY);
    DrawCubeWires((Vector3){5.0f, -0.1f, 5.0f}, 10.0f, 0.2f, 10.0f, DARKGRAY);

    for (const auto& edge : mesh.edges) {
        DrawLine3D((Vector3){edge.p1.x, edge.p1.y, edge.p1.z}, (Vector3){edge.p2.x, edge.p2.y, edge.p2.z}, LIGHTGRAY);
    }

    for (const auto& vertex : mesh.vertices) {
        DrawCube((Vector3){vertex.x, vertex.y, vertex.z}, 0.2f, 0.2f, 0.2f, DARKGRAY);
    }

    for (const auto& polygon : polygons) {
        for (size_t i = 0; i < polygon.vertices.size(); ++i) {
            const Point& p1 = polygon.vertices[i];
            const Point& p2 = polygon.vertices[(i + 1) % polygon.vertices.size()];
            DrawLine3D((Vector3){p1.x, p1.y, p1.z}, (Vector3){p2.x, p2.y, p2.z}, GREEN);
        }
    }

    for (const auto& obstacle : obstacles) {
        Vector3 pos = obstacle.getPosition();
        if (goalSet && segmentIntersectsObstacle(player.getPosition(), {goal.x, goal.y, goal.z}, pos, obstacleSize)) {
            DrawCube(pos, obstacleSize, obstacleSize, obstacleSize, RED);
        } else {
            DrawCube(pos, obstacleSize, obstacleSize, obstacleSize, GRAY);
        }
        DrawCubeWires(pos, obstacleSize, obstacleSize, obstacleSize, DARKGRAY);
    }

    if (pathThetaStar.size() >= 2) {
        for (size_t i = 0; i < pathThetaStar.size() - 1; i++) {
            DrawLine3D((Vector3){pathThetaStar[i].x, pathThetaStar[i].y, pathThetaStar[i].z}, (Vector3){pathThetaStar[i + 1].x, pathThetaStar[i + 1].y, pathThetaStar[i + 1].z}, PURPLE);
        }
    }

    DrawCube(player.getPosition(), 0.3f, 0.3f, 0.3f, BLUE);
    if (goalSet) {
        DrawCircle3D((Vector3){goal.x, goal.y, goal.z}, 0.5f, (Vector3){1, 0, 0}, 90.0f, BLUE);
    }

    EndMode3D();

    // Draw UI elements after the 3D scene
    DrawHealthBarAbovePlayer(player, camera);
    DrawHealthBar(player);
    DrawUI();

    EndDrawing();
}