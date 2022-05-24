#include "shaders\Shader.h"

#include "utils\ErrorSystem.h"
#include <fstream>
#include <vector>

Shader::~Shader()
{
    glDeleteProgram(ProgramId);
}

std::string Shader::ReadShader(const std::string& FilePath)
{
    std::ifstream InputStream(FilePath, std::ios::ate);
    if (!InputStream.is_open()) THROW_EXCEPTION(FILE_NOT_FOUND_ERROR)

    size_t Size = InputStream.tellg();
    if (Size<=0) THROW_EXCEPTION(EMPTY_FILE_ERROR)

    std::string Result;
    Result.resize(Size);
    
    InputStream.seekg(0, std::ios::beg);
    InputStream.read(&Result[0], Size);
    InputStream.close();

    return Result;
}

GLuint Shader::CreateShader(const std::string& FilePath, GLenum ShaderType)
{
    std::string ShaderStr = ReadShader(FilePath);
    const char* ShaderSource = ShaderStr.c_str();   
    GLuint ShaderId = glCreateShader(ShaderType);

    glShaderSource(ShaderId, 1, &ShaderSource, NULL);
    glCompileShader(ShaderId);    

    GLint Success;
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {   
        THROW_EXCEPTION(SHADER_ERROR)
    }

    return ShaderId;
}

GLuint Shader::CreateProgram(GLuint VertId, GLuint FragId)
{
    GLuint ProgramId = glCreateProgram();
    
    glAttachShader(ProgramId, VertId);
    glAttachShader(ProgramId, FragId);
    glLinkProgram(ProgramId);

    GLint Success;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Success);
    if (!Success)
    {   
        THROW_EXCEPTION(SHADER_ERROR)
    }

    glDeleteShader(VertId);
    glDeleteShader(FragId);
    
    return ProgramId;
}

void Shader::NewShader(const std::string& VertPath, const std::string& FragPath)
{
    GLuint VertId = CreateShader(VertPath, GL_VERTEX_SHADER);
    GLuint FragId = CreateShader(FragPath, GL_FRAGMENT_SHADER);
    static GLuint Id = CreateProgram(VertId, FragId);
    ProgramId = Id;
}