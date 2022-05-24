#pragma once

#include <vector>

class Object;

class Scene
{
protected:
    std::vector<Object*> Objects;

public:
    virtual ~Scene();    
    virtual void Init() = 0;
    virtual void Start();
    virtual void Update(float DeltaTime);
};