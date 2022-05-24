#include "components\RenderComponent.h"

RenderComponent::RenderComponent(Object& InOwner, Shader* InShader, const Mesh& InMesh) : Component(InOwner)
{
    RenderMaterial = Material(InShader);
    RenderMesh = InMesh;
}   

RenderComponent::~RenderComponent(){ }

void RenderComponent::Update(float DeltaTime){ }

void RenderComponent::Start()
{
    RenderMaterial.SetUp(RenderMesh);
}