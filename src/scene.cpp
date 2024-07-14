#include "scene.hpp"

void drawScene(const NavMesh& mesh, const std::vector<Polygon>& polygons, const std::vector<Vector3>& obstaclePositions, float obstacleSize, const Vector3& currentPositionThetaStar, bool goalSet, const Point& goal, const std::vector<Point>& pathThetaStar, const Camera3D& camera) {
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

    if (goalSet) {
        Vector3 goalVec = {goal.x, goal.y, goal.z};
        DrawLine3D(currentPositionThetaStar, goalVec, BLUE);

        for (const auto& pos : obstaclePositions) {
            if (segmentIntersectsObstacle(currentPositionThetaStar, goalVec, pos, obstacleSize)) {
                DrawCube(pos, obstacleSize, obstacleSize, obstacleSize, RED);
            } else {
                DrawCube(pos, obstacleSize, obstacleSize, obstacleSize, GRAY);
            }
            DrawCubeWires(pos, obstacleSize, obstacleSize, obstacleSize, DARKGRAY);
        }
    } else {
        for (const auto& pos : obstaclePositions) {
            DrawCube(pos, obstacleSize, obstacleSize, obstacleSize, GRAY);
            DrawCubeWires(pos, obstacleSize, obstacleSize, obstacleSize, DARKGRAY);
        }
    }

    if (pathThetaStar.size() >= 2) {
        for (size_t i = 0; i < pathThetaStar.size() - 1; i++) {
            DrawLine3D((Vector3){pathThetaStar[i].x, pathThetaStar[i].y, pathThetaStar[i].z}, (Vector3){pathThetaStar[i + 1].x, pathThetaStar[i + 1].y, pathThetaStar[i + 1].z}, PURPLE);
        }
    }

    DrawCube(currentPositionThetaStar, 0.3f, 0.3f, 0.3f, BLUE);
    if (goalSet) {
        DrawCircle3D((Vector3){goal.x, goal.y, goal.z}, 0.5f, (Vector3){ 1, 0, 0 }, 90.0f, BLUE);
    }

    EndMode3D();
    DrawFPS(10, 10);
    DrawText("Right-click to set goal point and start moving", 10, 40, 20, DARKGRAY);
    DrawText("Press R to reset obstacles", 10, 70, 20, DARKGRAY);
    EndDrawing();
}
