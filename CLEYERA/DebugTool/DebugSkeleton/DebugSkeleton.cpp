#include "DebugSkeleton.h"

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
#endif // _DEBUG

}

void DebugSkeleton::Draw(CameraData camera, SAnimation::Skeleton skeleton)
{
#ifdef _DEBUG

	jointObjectDesc_.colorDesc.color_ = Math::Vector::Vector4(jointColor_.x, jointColor_.y, jointColor_.z, 1.0f);
	Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix({ jointScale_,jointScale_,jointScale_ });
	for (int i = 0; i < jointSize_; i++)
	{
		jointWt_[i].matWorld = skeleton.joints[i].skeletonSpaceMatrix;
		jointWt_[i].matWorld = Math::Matrix::ScaleMatrixByAnother(jointWt_[i].matWorld, sm);
		jointWt_[i].TransfarMatrix();

		jointObject_->Draw(jointWt_[i], camera);
	}
#endif // _DEBUG

}

void DebugSkeleton::ImGuiUpdate()
{
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("DebugSkeleton"))
	{
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
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
#endif // _USE_IMGUI

}

void DebugSkeleton::CreateJoint(size_t size)
{
#ifdef _DEBUG

	jointWt_.resize(size);

	jointObjectDesc_.useLight = true;
	jointObjectDesc_.colorDesc.color_ = Math::Vector::Vector4(jointColor_.x, jointColor_.y, jointColor_.z,1.0f);
	jointModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");
	for (size_t i = 0; i < size; i++)
	{
		jointWt_[i].Initialize();
	}
	jointObject_ = make_unique<Game3dObject>();
	jointObject_->Create(make_unique<Phong3dPipline>());
	jointObject_->SetDesc(jointObjectDesc_);
	jointObject_->SetModel(jointModelHandle_);
#endif // _DEBUG

}
