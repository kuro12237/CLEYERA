#pragma once
#include"Pch.h"
#include"Model/primitive/LineModel.h"

namespace Engine::Particle
{
	/// <summary>
	/// ¦­΄oΜp[^
	/// </summary>
	struct  ParticleEmitControl
	{
		bool useFlag_ = false;
		float frequency = 0.0f;
		float frequencyTime = 0.0f;
		float flame = 0.0f;
	};

	/// <summary>
	/// emitterΜ`
	/// </summary>
	namespace EmitType {
		
		/// <summary>
		///  
		/// </summary>
		struct BoxParam
		{
			Math::Vector::Vector3 translate = {};
			Math::Vector::Vector3 rotate = {};
			Math::Matrix::Matrix4x4 matWorld = Math::Matrix::Identity();
			Math::Matrix::Matrix4x4 matVPV = Math::Matrix::Identity();
			uint32_t count = 0;
			uint32_t emit = 0;
			Math::Vector::Vector3 sizeMin = { -1.0f,-1.0f,-1.0f };
			Math::Vector::Vector3 sizeMax = { 1.0f,1.0f,1.0f };
			Math::Vector::Vector3 velocityMin = { 0.0f,0.0f,0.0f };
			Math::Vector::Vector3 velocityMax = { 0.0f,0.0f,0.0f };

			Math::Vector::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
			Math::Vector::Vector4 colorDecayMin = { 0.0f,0.0f,0.0f,0.01f };
			Math::Vector::Vector4 colorDecayMax = { 0.0f,0.0f,0.0f,0.01f };
			Math::Vector::Vector3 scaleVelocityMin = { 0.0f,0.0f,0.0f };
			Math::Vector::Vector3 scaleVelocityMax = { 0.0f,0.0f,0.0f };

			Math::Vector::Vector3 scaleSizeMin = { 1.0f,1.0f };
			Math::Vector::Vector3 scaleSizeMax = { 1.0f,1.0f };
		};
		/// <summary>
		/// ~
		/// </summary>
		struct Circle
		{
			Math::Vector::Vector3 translate = {};
			Math::Vector::Vector3 rotate = {};
			Math::Matrix::Matrix4x4 matWorld = Math::Matrix::Identity();
			Math::Matrix::Matrix4x4 matVPV = Math::Matrix::Identity();
			uint32_t count = 0;
			uint32_t emit = 0;
			float radious = 1.0f;

			Math::Vector::Vector3 velocityMin = {};
			Math::Vector::Vector3 velocityMax = {};

			Math::Vector::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
			Math::Vector::Vector4 colorDecayMin = { 0.0f,0.0f,0.0f,0.01f };
			Math::Vector::Vector4 colorDecayMax = { 0.0f,0.0f,0.0f,0.01f };

			Math::Vector::Vector3 scaleVelocityMin = {};
			Math::Vector::Vector3 scaleVelocityMax = {};

			Math::Vector::Vector3 scaleSizeMin = { 1.0f,1.0f,1.0f };
			Math::Vector::Vector3 scaleSizeMax = { 1.0f,1.0f,1.0f };
		};
		/// <summary>
		/// 
		/// </summary>
		struct SphereParam
		{
			Math::Vector::Vector3 translate = {};
			Math::Vector::Vector3 rotate = {};
			Math::Matrix::Matrix4x4 matWorld = Math::Matrix::Identity();
			Math::Matrix::Matrix4x4 matVPV = Math::Matrix::Identity();
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

			struct EffectData
			{

				float dissolveMask = 0.0f;
				Math::Vector::Vector2 dissolveEdgeMinMax = {};
				float pad1;

				Math::Vector::Vector4 dissolveEdgeColor = { 1.0f,1.0f,1.0f,1.0f };
			};
		}

#pragma region CreateLineObject
		void CreateSphere(unique_ptr <Primitive::LineModel>& lines, string name);
		void CreateBox(unique_ptr <Primitive::LineModel>& lines, string name);
		void CreateCircle(unique_ptr <Primitive::LineModel>& lines, string name);
#pragma endregion

#pragma region UpdateLineObject
		void UpdateBox(unique_ptr<Primitive::LineModel>& lines, EmitType::BoxParam box);
		void UpdateSphere(unique_ptr<Primitive::LineModel>& lines, EmitType::SphereParam sphere);
		void UpdateCircle(unique_ptr<Primitive::LineModel>& lines, EmitType::Circle circle);
#pragma endregion

	}
}
