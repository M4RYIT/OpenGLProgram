#include "shaders\TexProjRotShader.h"

#include "Mesh.h"
#include "Camera.h"
#include "Object.h"

TexProjRotShader::TexProjRotShader()
{
    NewShader("resources/shaders/tex_proj_rot.vert", "resources/shaders/tex.frag");
}

TexProjRotShader::~TexProjRotShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosUvVbo);
    glDeleteTextures(1, &Tex);
    Cam = nullptr;
    Obj = nullptr;
}

void TexProjRotShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    std::vector<float> TrianglesMesh;
    FlattenTriangles(InMesh, TrianglesMesh);

    glGenBuffers(1, &PosUvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosUvVbo);
    glBufferData(GL_ARRAY_BUFFER, TrianglesMesh.size() * sizeof(float), TrianglesMesh.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(ProgramId);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Tex);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glUniform1f(glGetUniformLocation(ProgramId, "aspect_ratio"), (GLfloat)AspectRatio);
    glUniform1f(glGetUniformLocation(ProgramId, "fov"), (GLfloat)Cam->Fov);
    glUniform1f(glGetUniformLocation(ProgramId, "near"), (GLfloat)Cam->Near);
    glUniform1f(glGetUniformLocation(ProgramId, "far"), (GLfloat)Cam->Far);    
}

void TexProjRotShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform3fv(glGetUniformLocation(ProgramId, "obj_pos"), 1, (GLfloat*)Obj->Tr.Position.data());
    glUniform3fv(glGetUniformLocation(ProgramId, "obj_rot"), 1, (GLfloat*)Obj->Tr.Rotation.data());
    glUniform3fv(glGetUniformLocation(ProgramId, "obj_scale"), 1, (GLfloat*)Obj->Tr.Scale.data());

    glDrawArrays(GL_TRIANGLES, 0, 36);
}