#pragma once

#include "singletons\Settings.h"
#include <vector>

class Object;
class Camera;

class Scene
{
protected:
    std::vector<Object*> Objects;
    Camera* Cam;
    std::vector<int> ViewportPos;
    std::vector<int> ViewportSize;

public:
    Scene(int X=0, int Y=0, int W=Settings::Get().WinData.Width, int H=Settings::Get().WinData.Height);
    virtual ~Scene();        
    virtual void Init() = 0;
    virtual void Start();
    virtual void Update(float DeltaTime);
};