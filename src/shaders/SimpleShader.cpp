#include "shaders\SimpleShader.h"
#include "Mesh.h"

SimpleShader::SimpleShader()
{
    NewShader("resources/shaders/simple.vert", "resources/shaders/simple.frag");
}

SimpleShader::~SimpleShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosVbo);
}

void SimpleShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &PosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.Vertices.size() * sizeof(float), InMesh.Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void SimpleShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}