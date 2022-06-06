#include "Camera.h"

Camera::Camera()
{
    Tr.Position = {0.f, 0.f, 0.f};
    Tr.Rotation = {0.f, 0.f, 0.f};
    Tr.Scale = {1.f, 1.f, 1.f};

    Fov = 60.f;
    Near = 0.01f;
    Far = 1000.f;
}

Camera::Camera(Transform InTransform, float InFov, float InNear, float InFar)
{
    Tr = InTransform;
    Fov = InFov;
    Near = InNear;
    Far = InFar;
}