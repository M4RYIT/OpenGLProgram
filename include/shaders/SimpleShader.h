#pragma once

#include "Shader.h"

class SimpleShader: public Shader
{
protected:
    GLuint PosVbo;

public:
    SimpleShader();
    ~SimpleShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;
};