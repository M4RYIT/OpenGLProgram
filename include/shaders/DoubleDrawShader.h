#pragma once

#include "shaders\Shader.h"
#include <vector>

class Camera;
class Object;

class DoubleDrawShader: public Shader
{
protected:
    GLuint PosUvVbo;   

public:
    enum MirrorFlags
    {
        None = 0,
        X = 1 << 0,
        Y = 1 << 1,
        Z = 1 << 2
    };

    DoubleDrawShader();
    ~DoubleDrawShader();

    virtual void Start(const Mesh& InMesh) override;
    virtual void Update(float DeltaTime) override;
    glm::vec3 GetMaxVert(const std::vector<float>& Vertices);
    glm::vec3 GetMinVert(const std::vector<float>& Vertices);

    GLuint Tex;
    Camera* Cam;
    Object* Obj;

    glm::mat4 Model;
    glm::mat4 View;
    glm::mat4 Projection;
    glm::vec3 VertexRange;

    float AspectRatio;
    int TrianglesCount;

    MirrorFlags Mirror;
};