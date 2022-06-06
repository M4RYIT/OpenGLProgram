#pragma once

#include <vector>

struct Triangle
{
    // 8 = pos(3)+uv(2)+norm(3)
    float V1[8];
    float V2[8];
    float V3[8];
};

struct Mesh
{
    std::vector<float> Vertices;
    std::vector<float> UVs;
    std::vector<float> Normals;
    std::vector<uint32_t> Indices;
    std::vector<Triangle> Triangles;
};

static void FlattenTriangles(const Mesh& InMesh, std::vector<float>& Out)
{
    Out.insert(Out.end(), (float*)InMesh.Triangles.data(), (float*)InMesh.Triangles.data() + InMesh.Triangles.size() * 24);
}