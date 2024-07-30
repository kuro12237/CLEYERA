#pragma once
#include"Pch.h"

struct SEmitterSphere
{
    Math::Vector::Vector3 translate;
    float radious;
    uint32_t count;
    float frequency;
    float frequencyTime;
    uint32_t emit;
};
