#pragma once

#include <vector>
#include "utils/MathOps.h"

struct Transform
{
    std::vector<float> Position;
    std::vector<float> Rotation;
    std::vector<float> Scale;

    std::vector<float> Forward()
    {
        std::vector<float> Direction = {0.f, 0.f, -1.f};
        Direction = Rotate(Direction, Rotation[0], 0);
        Direction = Rotate(Direction, Rotation[1], 1);
        Direction = Rotate(Direction, Rotation[2], 2);
        return Direction;
    }
};