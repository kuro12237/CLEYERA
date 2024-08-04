#pragma once
#include"Pch.h"


struct SEmitterSphere
{
	Math::Vector::Vector3 translate = {};
	float radious = 0;
	uint32_t count = 0;
	float frequency = 0.0f;
	float frequencyTime = 0.0f;
	uint32_t emit = 0;
	float flame = 0.0f;
};
