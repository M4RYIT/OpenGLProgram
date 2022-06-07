#pragma once

#include <glad\glad.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>

#define FLOAT(N) N##f
#define INT(N) N##i
#define UINT(N) N##ui
#define FLOAT_VECTOR(N) N##fv
#define INT_VECTOR(N) N##iv
#define UINT_VECTOR(N) N##uiv

struct Mesh;

class Shader
{    
protected:
    GLuint VaoId;   
    GLuint ProgramId; 
    bool bOverrideColor;
    bool bOverrideViewport;

    void NewShader(const std::string& VertPath, const std::string& FragPath);

public:
    virtual ~Shader();

    GLuint GetProgramId() { return ProgramId; };
    GLuint GetVaoId() { return VaoId; };
    bool OverrideColor() { return bOverrideColor; };
    bool OverrideViewport() { return bOverrideViewport; };

    static std::string ReadShader(const std::string& FilePath);
    static GLuint CreateShader(const std::string& FilePath, GLenum ShaderType);
    static GLuint CreateProgram(GLuint InVertId, GLuint InFragId);
    static GLuint CreateTexture(const std::string& ImgPath);
    static glm::vec3 ToVec3(std::vector<float> From);
    static glm::vec3 ToVec3InvZ(std::vector<float> From);
    virtual void Update(float DeltaTime) = 0;
    virtual void Start(const Mesh& InMesh) = 0;    
};