#pragma once

#include "Scene.h"

class TestScene: public Scene
{
public:
    TestScene();
    TestScene(int X, int Y, int W, int H);
    virtual void Init();

    void SimpleTriangle();
    void SimpleIndexQuad();
    void ColorMulQuad();
    void TexBlend();
    void TexProj();
    void TexProjRot();
    void MvpPhong();
};