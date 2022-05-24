#pragma once

#include "shaders\Shader.h"

class IndexShader: public Shader
{
protected:
    GLuint PosVbo;
    GLuint Ebo;
public:
    IndexShader();
    ~IndexShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;
};