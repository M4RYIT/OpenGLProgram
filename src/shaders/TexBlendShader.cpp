#include "shaders\TexBlendShader.h"

#include "Mesh.h"

TexBlendShader::TexBlendShader() : ElapsedTime(0.f)
{
    NewShader("resources/shaders/tex.vert", "resources/shaders/tex_blend.frag");
}

TexBlendShader::~TexBlendShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosVbo);
    glDeleteBuffers(1, &UvVbo);
    glDeleteBuffers(1, &Ebo);
    glDeleteTextures(1, &Tex1);
    glDeleteTextures(1, &Tex2);
}

void TexBlendShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &PosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.Vertices.size() * sizeof(float), InMesh.Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &UvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.UVs.size() * sizeof(float), InMesh.UVs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, InMesh.Indices.size() * sizeof(uint32_t), InMesh.Indices.data(), GL_STATIC_DRAW);

    glUseProgram(ProgramId);
    glUniform4fv(glGetUniformLocation(ProgramId, "base_color"), 1, (GLfloat*)BaseColor.data());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Tex1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Tex2);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TexBlendShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    ElapsedTime += DeltaTime;
    float BlendFactor = sinf(ElapsedTime) * 0.5f + 0.5f;    
    glUniform1f(glGetUniformLocation(ProgramId, "blend_factor"), (GLfloat)BlendFactor);
}