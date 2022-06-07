#pragma once

#include "shaders\Shader.h"
#include <vector>

class Camera;
class Object;
class PointLightComponent;

class MvpPhongShader: public Shader
{
protected:
    GLuint PosUvNormVbo;

public:
    MvpPhongShader();
    ~MvpPhongShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;

    GLuint Tex;
    Camera* Cam;
    Object* Obj;
    PointLightComponent* PointLight;
    
    float AspectRatio;
    float AmbientFactor;
    float SpecularFactor;
    
    int TrianglesCount;

    glm::mat4 Model;
    glm::mat4 View;
    glm::mat4 Projection;
};