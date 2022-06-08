#include "shaders/MvpPhongShader.h"

#include "Camera.h"
#include "Object.h"
#include "Mesh.h"
#include "components/PointLightComponent.h"
#include <glm/gtc/matrix_transform.hpp>

MvpPhongShader::MvpPhongShader()
{
    NewShader("resources/shaders/mvp.vert", "resources/shaders/phong.frag");
}

MvpPhongShader::~MvpPhongShader()
{
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(1, &PosUvNormVbo);
    glDeleteTextures(1, &Tex);
    Cam = nullptr;
    Obj = nullptr;
    PointLight = nullptr;
}

void MvpPhongShader::Start(const Mesh& InMesh)
{
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    std::vector<float> TrianglesMesh;
    FlattenTriangles(InMesh, TrianglesMesh);
    TrianglesCount = TrianglesMesh.size() / 8;

    glGenBuffers(1, &PosUvNormVbo);
    glBindBuffer(GL_ARRAY_BUFFER, PosUvNormVbo);
    glBufferData(GL_ARRAY_BUFFER, TrianglesMesh.size() * sizeof(float), TrianglesMesh.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glUseProgram(ProgramId);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Tex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);    

    glUniform1f(glGetUniformLocation(ProgramId, "ambient_factor"), (GLfloat)AmbientFactor);
    glUniform1f(glGetUniformLocation(ProgramId, "specular_factor"), (GLfloat)SpecularFactor);
}

void MvpPhongShader::Update(float DeltaTime)
{
    glUseProgram(ProgramId);
    glBindVertexArray(VaoId);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    glUniform3fv(glGetUniformLocation(ProgramId, "point_light_pos"), 1, (GLfloat*)PointLight->Owner.Tr.Position.data());
    glUniform3fv(glGetUniformLocation(ProgramId, "camera_pos"), 1, (GLfloat*)Cam->Tr.Position.data());
    glUniform4fv(glGetUniformLocation(ProgramId, "light_col"), 1, (GLfloat*)&PointLight->LightColor);
    glUniform1f(glGetUniformLocation(ProgramId, "light_intensity"), (GLfloat)PointLight->LightIntensity);

    glDrawArrays(GL_TRIANGLES, 0, TrianglesCount);
}