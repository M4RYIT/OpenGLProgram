#include "shaders\IndexShader.h"
#include "Mesh.h"

IndexShader::IndexShader()
{
    NewShader("resources/shaders/simple.vert", "resources/shaders/simple.frag");
}

IndexShader::~IndexShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosVbo);
    glDeleteBuffers(1, &Ebo);
}

void IndexShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &PosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.VertsPosition.size() * sizeof(float), InMesh.VertsPosition.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, InMesh.VertsIndex.size() * sizeof(uint32_t), InMesh.VertsIndex.data(), GL_STATIC_DRAW);
}

void IndexShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glBindVertexArray(0);
}
