#pragma once

#include "shaders\Shader.h"
#include <vector>

class ColorMulShader: public Shader
{
protected:
    GLuint PosVbo;
    GLuint ColVbo;
    GLuint Ebo;

    float ElapsedTime;
public:
    ColorMulShader();
    ~ColorMulShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;

    std::vector<float> BaseColor;
    std::vector<float> VertsColors;
};