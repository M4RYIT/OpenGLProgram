#pragma once

#include "Component.h"
#include "shaders\Shader.h"
#include "Mesh.h"

class RenderComponent : public Component
{
public:
    Shader* RenderMaterial;
    Mesh RenderMesh;

    RenderComponent(Object& InOwner, Shader* InShader, const Mesh& InMesh);
    ~RenderComponent();
    virtual void Update(float DeltaTime);
    virtual void Start();
};