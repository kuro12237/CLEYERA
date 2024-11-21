#include "DebugSkeleton.h"

using namespace Engine::Transform;
using namespace Engine::Debug;
using namespace Engine::Manager;
using namespace Engine::Objects;

void DebugSkeleton::Create(SAnimation::Skeleton skeleton, WorldTransform w)
{
#ifdef _DEBUG
	wT_ = &w;
	jointSize_ = skeleton.joints.size();

	numberString_.resize(jointSize_);
	for (int i = 0; i < jointSize_; ++i) {
		numberString_[i] = std::to_string(i);
	}

	CreateJoint(jointSize_);
	lineSize_ = jointSize_;
	lineModels_.resize(lineSize_);

	for (size_t i = 0; i < lineSize_; i++)
	{
		lineModels_[i] = make_unique<Primitive::LineModel>();
		lineModels_[i]->Create("skeleton");
	}

#endif // _DEBUG

}

void DebugSkeleton::Draw(WorldTransform w, SAnimation::Skeleton skeleton)
{
#ifdef _DEBUG
	if (jointDrawFlag_)
	{
		JointDraw(w, skeleton);
	}
	if (lineDrawFlag_)
	{
		SkeletonDraw(w, skeleton, skeleton.root);
	}
#endif // _DEBUG

}

void DebugSkeleton::ImGuiUpdate()
{
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("DebugSkeleton"))
	{
		ImGui::Checkbox("LineDrawFlag", &lineDrawFlag_);
		ImGui::Checkbox("JointDrawFlag", &jointDrawFlag_);

		if (ImGui::TreeNode("Joint"))
		{
			ImGui::DragFloat("scale", &jointScale_, -0.1f, 0.1f);
			ImGui::ColorPicker3("color", &jointColor_.x);
			if (ImGui::TreeNode("WorldPos"))
			{
				for (size_t i = 0; i < jointSize_; i++)
				{
					ImGui::Text("%s :: %f,%f,%f", numberString_[i].c_str(), jointWt_[i].GetWorldPosition().x, jointWt_[i].GetWorldPosition().y, jointWt_[i].GetWorldPosition().z);
				}
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
#endif // _USE_IMGUI

}

void DebugSkeleton::CreateJoint(size_t size)
{
	size;
#ifdef _DEBUG

	jointWt_.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		jointWt_[i].Initialize();
	}

	jointObjectDesc_.useLight = true;
	jointObjectDesc_.colorDesc.color_ = Math::Vector::Vector4(jointColor_.x, jointColor_.y, jointColor_.z, 1.0f);
	jointModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");

	jointObject_ = make_unique<Game3dObject>();
	jointObject_->Create(make_unique<Phong3dPipline>());
	jointObject_->SetDesc(jointObjectDesc_);
	jointObject_->SetModel(jointModelHandle_);
#endif // _DEBUG
}

void DebugSkeleton::SkeletonDraw(WorldTransform w, const SAnimation::Skeleton& skeleton, uint32_t index)
{
	const SAnimation::Joint& parentJoint = skeleton.joints[index];
	for (int32_t childIndex : parentJoint.childlen)
	{
		const SAnimation::Joint& childJoint = skeleton.joints[childIndex];
		Math::Vector::Vector3 start = { parentJoint.skeletonSpaceMatrix.m[3][0],parentJoint.skeletonSpaceMatrix.m[3][1],parentJoint.skeletonSpaceMatrix.m[3][2] };
		Math::Vector::Vector3 end = { childJoint.skeletonSpaceMatrix.m[3][0],childJoint.skeletonSpaceMatrix.m[3][1],childJoint.skeletonSpaceMatrix.m[3][2] };
		lineModels_[childIndex]->SetWorldMat(w.matWorld);
		lineModels_[childIndex]->Draw();
		SkeletonDraw(w, skeleton, childIndex);
	}
}

void DebugSkeleton::JointDraw(const WorldTransform w, const SAnimation::Skeleton& skeleton)
{
	jointObjectDesc_.colorDesc.color_ = Math::Vector::Vector4(jointColor_.x, jointColor_.y, jointColor_.z, 1.0f);
	Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix({ jointScale_,jointScale_,jointScale_ });
	for (int i = 0; i < jointSize_; i++)
	{
		jointWt_[i].matWorld = Math::Matrix::Multiply(skeleton.joints[i].skeletonSpaceMatrix, w.matWorld);
		jointWt_[i].matWorld = Math::Matrix::ScaleMatrixByAnother(jointWt_[i].matWorld, sm);
		jointWt_[i].TransfarMatrix();

		jointObject_->Draw(jointWt_[i]);
	}
}
