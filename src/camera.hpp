#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"
#include "vector_math.hpp"

Camera InitCamera();
void HandleCameraMovement(Camera &camera, Vector3 currentPositionThetaStar, bool &cameraAttached);

#endif
