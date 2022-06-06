#include "singletons\Renderer.h"

#include "shaders\Shader.h"

Renderer::~Renderer()
{
    Shaders.clear();
}

void Renderer::ClearShaders()
{
    Shaders.clear();
}

Renderer& Renderer::Get()
{
    static Renderer* Rnd = nullptr;

    if (!Rnd) Rnd = new Renderer();

    return *Rnd;
}

void Renderer::AddShader(Shader* InShader)
{
    Shaders.push_back(InShader);
}

void Renderer::Update(float DeltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (Shader*& Shader : Shaders)
    {   
        Shader->Update(DeltaTime);
    }
}

void Renderer::SetViewport(int X, int Y, int Width, int Height)
{
    glViewport(X, Y, Width, Height);
}

void Renderer::SetBackgroundColor(float R, float G, float B, float A)
{
    glClearColor(R, G, B, A);
}