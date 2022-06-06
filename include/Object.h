#pragma once

#include "Transform.h"
#include <vector>

class Component;

class Object
{
public:
    Transform Tr;
    std::vector<Component*> Components;

    Object();
    Object(Transform InTransform);
    ~Object();

    void AddComponent(Component* Component);
    void Start();
    void Update(float DeltaTime);
};