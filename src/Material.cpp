#include "Material.h"

#include "singletons\Renderer.h"

Material::Material(Shader* InShader) : MatShader(InShader)
{
    Renderer::Get().AddShader(InShader);
}

void Material::SetUp(Mesh& InMesh)
{
    MatShader->Start(InMesh);
}

GLuint Material::Id()
{
    return MatShader->GetProgramId();
}