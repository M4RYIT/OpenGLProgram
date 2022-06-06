#pragma once

#include "Transform.h"

class Camera
{
public:
    Transform Tr;
    float Fov;
    float Near;
    float Far;

    Camera();
    Camera(Transform InTransform, float InFov, float InNear, float InFar);
    ~Camera() = default;
};