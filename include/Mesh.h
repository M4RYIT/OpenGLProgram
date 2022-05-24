#pragma once

#include <vector>

struct Mesh
{
    std::vector<float> VertsPosition;
    std::vector<float> VertsColors;
    std::vector<uint32_t> VertsIndex;
};