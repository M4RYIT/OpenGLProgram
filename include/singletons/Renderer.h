#pragma once

#include <glad/glad.h>
#include <vector>

class Shader;

class Renderer
{
private:
    std::vector<Shader*> Shaders;


public:
    ~Renderer();

    static Renderer& Get();
    void AddShader(Shader* InShader);
    void Update(float DeltaTime);
    void SetViewport(int X, int Y, int Width, int Height);
    void SetBackgroundColor(float R, float G, float B, float A);
};
