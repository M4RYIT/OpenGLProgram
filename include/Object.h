#pragma once

#include <vector>

class Component;

class Object
{
public:
    //Transform

    std::vector<Component*> Components;

    Object() = default;
    ~Object();

    void AddComponent(Component* Component);
    void Start();
    void Update(float DeltaTime);
};