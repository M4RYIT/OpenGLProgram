#pragma once

#include <glad\glad.h>
#include "shaders\Shader.h"

#define SET_PARAMETER(Id, Name, Type, ...) glUniform##Type(glGetUniformLocation(Id, #Name), __VA_ARGS__)
#define SET_VECTOR(Id, Name, Type, Value) glUniform##Type(glGetUniformLocation(Id, #Name), 1, Value)
#define SET_MATRIX(Id, Name, Type, ...) glUniformMatrix##Type##fv(glGetUniformLocation(Id, #Name), 1, GL_TRUE, __VA_ARGS__)

class Mesh;

class Material
{
private:
    Shader* MatShader;

public:
    Material() = default;
    Material(Shader* InShader);
    void SetUp(Mesh& InMesh);
    GLuint Id();
};