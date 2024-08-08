#pragma once
#include"Pch.h"
#include"Model/primitive/LineModel.h"

namespace Particle
{
	struct  ParticleEmitControl
	{
		bool useFlag_ = false;
		float frequency = 0.0f;
		float frequencyTime = 0.0f;
		float flame = 0.0f;
	};
	namespace EmitType {

		struct BoxParam
		{
			Math::Vector::Vector3 translate = {};
			Math::Vector::Vector3 rotate = {};
			uint32_t count = 0;
			uint32_t emit = 0;
			Math::Vector::Vector3 sizeMin = { -1.0f,-1.0f,-1.0f };
			Math::Vector::Vector3 sizeMax = { 1.0f,1.0f,1.0f };
		};

		struct SphereParam
		{
			Math::Vector::Vector3 translate = {};
			Math::Vector::Vector3 rotate = {};
			uint32_t count = 0;
			uint32_t emit = 0;
			float radious = 1.0f;
		};
	}
	namespace System
	{
		namespace StructData
		{
			struct  ParticleVertexData
			{
				Math::Vector::Vector4 position;
				Math::Vector::Vector2 texcoord;
				Math::Vector::Vector3 normal;
				uint32_t instancedId;
			};

		
		}
		void CreateSphere(unique_ptr <Primitive::LineModel>& lines, string name);
		void CreateBox(unique_ptr <Primitive::LineModel>& lines, string name);

		void UpdateBox(unique_ptr<Primitive::LineModel>& lines, EmitType::BoxParam box);
		void UpdateSphere(unique_ptr<Primitive::LineModel>& lines, EmitType::SphereParam sphere);
	}
}
