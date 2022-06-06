#pragma once

#include "Component.h"
#include <vector>

class RotatorComponent: public Component
{
public:
    std::vector<float> RotStep;

    RotatorComponent(Object& InOwner, float RotX, float RotY, float RotZ);
    ~RotatorComponent();
    virtual void Update(float DeltaTime);
    virtual void Start();
};