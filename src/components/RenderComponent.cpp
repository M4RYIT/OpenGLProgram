#include "components\RenderComponent.h"
#include "singletons\Renderer.h"

RenderComponent::RenderComponent(Object& InOwner, Shader* InShader, const Mesh& InMesh) : Component(InOwner)
{
    Renderer::Get().AddShader(InShader);
    RenderMaterial = InShader;
    RenderMesh = InMesh;
}   

RenderComponent::~RenderComponent(){ }

void RenderComponent::Update(float DeltaTime){ }

void RenderComponent::Start()
{
    RenderMaterial->Start(RenderMesh);
}