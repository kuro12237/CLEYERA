#pragma once
#include"Pch.h"

namespace Particle
{
	struct  ParticleVertexData
	{
		Math::Vector::Vector4 position;
		Math::Vector::Vector2 texcoord;
		Math::Vector::Vector3 normal;
		uint32_t instancedId;
	};
}