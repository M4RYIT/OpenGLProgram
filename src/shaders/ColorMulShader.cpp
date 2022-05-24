#include "shaders\ColorMulShader.h"

#include "Mesh.h"
#include "Color.h"

ColorMulShader::ColorMulShader()
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
    glBufferData(GL_ARRAY_BUFFER, InMesh.VertsPosition.size() * sizeof(float), InMesh.VertsPosition.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ColVbo);
    glBindBuffer(GL_ARRAY_BUFFER, ColVbo);
    glBufferData(GL_ARRAY_BUFFER, InMesh.VertsColors.size() * sizeof(float), InMesh.VertsColors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, InMesh.VertsIndex.size() * sizeof(uint32_t), InMesh.VertsIndex.data(), GL_STATIC_DRAW);
}

void ColorMulShader::Update(float DeltaTime)
{    
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    
    Color BaseColor;
    glGetnUniformfv(ProgramId,glGetUniformLocation(ProgramId, "base_color"), 4 * sizeof(float), (GLfloat*)&BaseColor);

    BaseColor.R = sinf(BaseColor.R + DeltaTime) * 0.5f + 0.5f;
    BaseColor.G = sinf(BaseColor.G + DeltaTime) * 0.5f + 0.5f;
    BaseColor.B = sinf(BaseColor.B + DeltaTime) * 0.5f + 0.5f;
    BaseColor.A = 1.f;
    glUniform4fv(glGetUniformLocation(ProgramId, "base_color"), 1, (GLfloat*)&BaseColor);

    glBindVertexArray(0);
}