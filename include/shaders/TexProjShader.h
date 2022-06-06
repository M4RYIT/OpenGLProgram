#pragma once

#include "shaders\Shader.h"
#include <vector>

class TexProjShader: public Shader
{
protected:
    GLuint PosVbo;
    GLuint UvVbo;
    GLuint Ebo;
    
    float ElapsedTime;

public:
    TexProjShader();
    ~TexProjShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;

    std::vector<float> BaseColor;
    GLuint Tex1;
    GLuint Tex2;
};
