#pragma once

class Object;

class Component
{
public:
    Object& Owner;

    Component(Object& InOwner);
    virtual void Update(float DeltaTime) = 0;
    virtual void Start() = 0;
};