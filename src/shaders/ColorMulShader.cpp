#include "shaders\ColorMulShader.h"

#include "Mesh.h"

ColorMulShader::ColorMulShader() : ElapsedTime(0.f)
{
    NewShader("resources/shaders/color_mul.vert", "resources/shaders/color_mul.frag");
}

ColorMulShader::~ColorMulShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosVbo);
    glDeleteBuffers(1, &ColVbo);
    glDeleteBuffers(1, &Ebo);
}

void ColorMulShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &PosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.Vertices.size() * sizeof(float), InMesh.Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ColVbo);
    glBindBuffer(GL_ARRAY_BUFFER, ColVbo);
    glBufferData(GL_ARRAY_BUFFER, VertsColors.size() * sizeof(float), VertsColors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, InMesh.Indices.size() * sizeof(uint32_t), InMesh.Indices.data(), GL_STATIC_DRAW);
}

void ColorMulShader::Update(float DeltaTime)
{    
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    
    ElapsedTime += DeltaTime;

    std::vector<float> Color(4);
    Color[0] = sinf(BaseColor[0] + ElapsedTime) * 0.5f + 0.5f;
    Color[1] = sinf(BaseColor[1] + ElapsedTime) * 0.5f + 0.5f;
    Color[2] = sinf(BaseColor[2] + ElapsedTime) * 0.5f + 0.5f;
    Color[3] = 1.f;
    glUniform4fv(glGetUniformLocation(ProgramId, "base_color"), 1, (GLfloat*)Color.data());
}