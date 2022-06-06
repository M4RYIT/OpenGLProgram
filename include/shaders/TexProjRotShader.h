#pragma once

#include "shaders\Shader.h"
#include <vector>

class Camera;
class Object;

class TexProjRotShader: public Shader
{
protected:
    GLuint PosUvVbo;

public:
    TexProjRotShader();
    ~TexProjRotShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;

    GLuint Tex;
    Camera* Cam;
    Object* Obj;
    float AspectRatio;
};