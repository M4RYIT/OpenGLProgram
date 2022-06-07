#pragma once

#include <vector>

#define PI 3.14159265

static std::vector<float> Rotate(const std::vector<float>& V, float Angle, int Axis)
{
    float Rad = Angle * PI / 180.f;
    int Index1 = (Axis + 1)%3;
    int Index2 = (Axis + 2)%3;

    std::vector<float> Rotated = {V[0], V[1], V[2]};
    Rotated[Index1] = cosf(Rad) * V[Index1] - sinf(Rad) * V[Index2];
    Rotated[Index2] = sinf(Rad) * V[Index1] + cosf(Rad) * V[Index2];
    return Rotated;
}