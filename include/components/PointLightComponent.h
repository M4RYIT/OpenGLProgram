#pragma once

#include "Color.h"
#include "Component.h"
#include <vector>

class PointLightComponent: public Component
{
public:
    float LightIntensity;
    Color LightColor;

    PointLightComponent(Object& InOwner, float Intensity, Color Col);
    ~PointLightComponent() = default;
    virtual void Update(float DeltaTime);
    virtual void Start();
};