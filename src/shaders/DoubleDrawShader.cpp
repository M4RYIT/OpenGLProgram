#include "shaders/DoubleDrawShader.h"

#include "Mesh.h"
#include "Camera.h"
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

DoubleDrawShader::DoubleDrawShader()
{
    NewShader("resources/shaders/mvp.vert", "resources/shaders/tex.frag");
}

DoubleDrawShader::~DoubleDrawShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosUvVbo);
    glDeleteTextures(1, &Tex);
    Cam = nullptr;
    Obj = nullptr;
}

glm::vec3 DoubleDrawShader::GetMaxVert(const std::vector<float>& Vertices)
{
    glm::vec3 MaxVert = glm::vec3(Vertices[0], Vertices[1], Vertices[2]);
    for (int i=0; i<Vertices.size(); i+=3)
    {
        if (Vertices[i] > 1.0f)
        {
            int c = 3;
        }
        if (Vertices[i] > MaxVert.x) MaxVert.x = Vertices[i];
        if (Vertices[i + 1] > MaxVert.y) MaxVert.y = Vertices[i + 1];
        if (Vertices[i + 2] > MaxVert.z) MaxVert.z = Vertices[i + 2];
    }
    return MaxVert;
}

void DoubleDrawShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    std::vector<float> TrianglesMesh;
    FlattenTriangles(InMesh, TrianglesMesh);
    TrianglesCount = TrianglesMesh.size()/8;
    MaxVertex = GetMaxVert(InMesh.Vertices);

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
}

void DoubleDrawShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFrontFace(GL_CCW);

    View = glm::lookAt(ToVec3(Cam->Tr.Position), 
                       ToVec3(Cam->Tr.Position) + ToVec3(Cam->Tr.Forward()),
                       glm::vec3{0.f, 1.f, 0.f});
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, "view"), 1, GL_FALSE, &View[0][0]);
    
    Projection = glm::perspective(glm::radians(Cam->Fov), AspectRatio, Cam->Near, Cam->Far);
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, "projection"), 1, GL_FALSE, &Projection[0][0]);

    Model = glm::mat4(1.f);
    Model = glm::translate(Model, ToVec3(Obj->Tr.Position));
    Model = glm::rotate(Model, glm::radians(Obj->Tr.Rotation[0]), glm::vec3(1.f, 0.f, 0.f));
    Model = glm::rotate(Model, glm::radians(Obj->Tr.Rotation[1]), glm::vec3(0.f, 1.f, 0.f));
    Model = glm::rotate(Model, glm::radians(Obj->Tr.Rotation[2]), glm::vec3(0.f, 0.f, 1.f));
    Model = glm::scale(Model, ToVec3(Obj->Tr.Scale));
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, "model"), 1, GL_FALSE, &Model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, TrianglesCount);

    if (Mirror & (X|Y|Z))
    {
        glFrontFace(GL_CW);    
    }   
    
    glm::vec3 MirrorScale = ToVec3(Obj->Tr.Scale);
    MirrorScale.x *= (Mirror & X)?-1.f:1.f;
    MirrorScale.y *= (Mirror & Y)?-1.f:1.f;
    MirrorScale.z *= (Mirror & Z)?-1.f:1.f;

    glm::vec3 MirrorPos = ToVec3(Obj->Tr.Position);
    MirrorPos.x += MaxVertex.x * 2.f * ((Mirror & X)?-MirrorScale.x:0.f);
    MirrorPos.y += MaxVertex.y * 2.f * ((Mirror & Y)?MirrorScale.y:0.f);
    MirrorPos.z += MaxVertex.z * 2.f * ((Mirror & Z)?MirrorScale.z:0.f);

    glm::vec3 MirrorRot = ToVec3(Obj->Tr.Rotation);
    MirrorRot.x *= (Mirror & (Y|Z))?-1.f:1.f;
    MirrorRot.y *= (Mirror & (X|Z))?-1.f:1.f;
    MirrorRot.z *= (Mirror & (X|Y))?-1.f:1.f;

    Model = glm::mat4(1.f);
    Model = glm::translate(Model, MirrorPos);
    Model = glm::rotate(Model, glm::radians(MirrorRot.x), glm::vec3(1.f, 0.f, 0.f));
    Model = glm::rotate(Model, glm::radians(MirrorRot.y), glm::vec3(0.f, 1.f, 0.f));
    Model = glm::rotate(Model, glm::radians(MirrorRot.z), glm::vec3(0.f, 0.f, 1.f));
    Model = glm::scale(Model, MirrorScale);
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, "model"), 1, GL_FALSE, &Model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, TrianglesCount);
}