#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"
#include "VectorMath.hpp"

Camera InitCamera();
void HandleCameraMovement(Camera &camera, Vector3 currentPositionThetaStar, bool &cameraAttached);

#endif
