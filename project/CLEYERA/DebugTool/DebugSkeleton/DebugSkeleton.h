#pragma once
#include"GraphicsPipelineManager.h"
#include"CreateResource.h"
#include"CameraData.h"
#include"ModelManager.h"
#include"Game3dObject.h"
#include"Model/primitive/LineModel.h"

namespace Engine::Debug
{
	/// <summary>
	/// skinningのデバッグ用の表示
	/// </summary>
	class DebugSkeleton
	{
	public:
		DebugSkeleton() {};
		~DebugSkeleton() {};

		void Create(SAnimation::Skeleton skeleton, Engine::Transform::WorldTransform w);

		void Draw(Engine::Transform::WorldTransform w, SAnimation::Skeleton skeleton);

		void ImGuiUpdate();
	private:

		void CreateJoint(size_t size);

		void SkeletonDraw(Engine::Transform::WorldTransform w, const SAnimation::Skeleton& skeleton, uint32_t index);

		void JointDraw(const Engine::Transform::WorldTransform w, const SAnimation::Skeleton& skeleton);

		const Engine::Transform::WorldTransform* wT_;
		vector<string>numberString_;

		size_t jointSize_ = 0;

		float jointScale_ = 1.0f;
		Math::Vector::Vector3 jointColor_ = { 0.0f,1.0f,0.0f };
		uint32_t jointModelHandle_ = 0;
		Game3dObjectDesc jointObjectDesc_ = {};
		vector<Engine::Transform::WorldTransform>jointWt_;
		unique_ptr<Engine::Objects::Game3dObject>jointObject_;

		size_t lineSize_ = 0;
		vector<unique_ptr<Primitive::LineModel>>lineModels_{};

		bool lineDrawFlag_ = false;
		bool jointDrawFlag_ = false;

	};
}