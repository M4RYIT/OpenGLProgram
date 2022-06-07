#include "shaders\Shader.h"

#include "utils\ErrorSystem.h"
#include "utils\stb_image.h"
#include <fstream>
#include <vector>

Shader::~Shader()
{
    glDeleteProgram(ProgramId);
}

glm::vec3 Shader::ToVec3InvZ(std::vector<float> From)
{
    return glm::vec3(From[0], From[1], -From[2]);
}

glm::vec3 Shader::ToVec3(std::vector<float> From)
{
    return glm::vec3(From[0], From[1], From[2]);
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

GLuint Shader::CreateTexture(const std::string& ImgPath)
{
    stbi_set_flip_vertically_on_load(true);
    int Width, Height, Channels;
    unsigned char* Data = stbi_load(ImgPath.c_str(), &Width, &Height, &Channels, 0);
    if (!Data) THROW_EXCEPTION(FILE_NOT_FOUND_ERROR)

    GLenum Format = Channels == 3 ? GL_RGB : GL_RGBA;

    GLuint TextureId;
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    //Load Data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);
    //Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Mimapping (Optional)
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);
    stbi_set_flip_vertically_on_load(false);
    return TextureId;
}

void Shader::NewShader(const std::string& VertPath, const std::string& FragPath)
{
    GLuint VertId = CreateShader(VertPath, GL_VERTEX_SHADER);
    GLuint FragId = CreateShader(FragPath, GL_FRAGMENT_SHADER);
    static GLuint Id = CreateProgram(VertId, FragId);
    ProgramId = Id;
}