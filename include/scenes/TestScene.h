#pragma once

#include "Scene.h"

class TestScene: public Scene
{
public:
    virtual void Init();

    void SimpleTriangle();
    void SimpleIndexQuad();
    void ColorMulQuad();
};