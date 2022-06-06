#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "Mesh.h"

bool ParseObj(const std::string& Path, Mesh& OutMesh);

#ifdef OBJ_PARSER_IMPLEMENTATION
void ParseLine(std::string& InStr, const std::string& Delims, std::vector<float>& Values)
{
    size_t Start, Pos = 0;
    while((Start = InStr.find_first_not_of(Delims, Pos)) != std::string::npos)
    {
        Pos = InStr.find_first_of(Delims, Start + 1);
        // GetValue
        Values.push_back(std::stof(InStr.substr(Start, Pos - Start)));
    }
}

void ParseLine(std::string& InStr, const std::string& Delims, std::vector<uint32_t>& Values)
{
    size_t Start, Pos = 0;
    while((Start = InStr.find_first_not_of(Delims, Pos)) != std::string::npos)
    {
        Pos = InStr.find_first_of(Delims, Start + 1);
        // GetValue
        Values.push_back(std::stoi(InStr.substr(Start, Pos - Start)));
    }
}

Triangle GetTriangle(uint32_t* Indices, float* Vertices, float* Uvs, float* Normals)
{
    Triangle OutTr;
    float* TrPtr = (float*)&OutTr;

    for (int Vertex=0; Vertex<3; Vertex++)
    {
        int TrIndex = Vertex * 8;
        
        uint32_t Index = Indices[Vertex * 3] - 1;
        std::memcpy(TrPtr + TrIndex, Vertices + Index * 3, sizeof(float) * 3); // Vert Pos
        
        Index = Indices[(Vertex * 3) + 1] - 1;
        std::memcpy(TrPtr + TrIndex + 3, Uvs + Index * 2, sizeof(float) * 2);

        Index = Indices[(Vertex * 3) + 2] - 1;
        std::memcpy(TrPtr + TrIndex + 5, Normals + Index * 3, sizeof(float) * 3);        
    }

    return OutTr;
}

bool ParseObj(const std::string& Path, Mesh& OutMesh)
{
    std::ifstream FileStream(Path);
    if (!FileStream.is_open()) return false;

    for (std::string line; std::getline(FileStream, line); )
    {
        if (line.rfind("v ", 0) == 0) ParseLine(line, "v ", OutMesh.Vertices);

        if (line.rfind("vt ", 0) == 0) ParseLine(line, "vt ", OutMesh.UVs);

        if (line.rfind("vn ", 0) == 0) ParseLine(line, "vn ", OutMesh.Normals);

        if (line.rfind("f ", 0) == 0) ParseLine(line, "f /", OutMesh.Indices);
    }

    FileStream.close();

    std::vector<float[8]> b;

    for (int TrIndex=0; TrIndex<OutMesh.Indices.size(); TrIndex+=9)
    {
        OutMesh.Triangles.push_back(GetTriangle(OutMesh.Indices.data() + TrIndex, 
                                                OutMesh.Vertices.data(),
                                                OutMesh.UVs.data(),
                                                OutMesh.Normals.data()));
    }

    return true;
}
#endif //OBJ_PARSER_IMPLEMENTATION