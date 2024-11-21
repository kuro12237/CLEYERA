#include "AnimationManager.h"

using namespace Math::Vector;
using namespace Math::Matrix;
using namespace Math::Qua;
using namespace Engine::Manager;
using namespace Engine::Transform;

AnimationManager* AnimationManager::GetInstance()
{
	static AnimationManager instance;
	return &instance;
}

uint32_t AnimationManager::LoadAnimation(const string& fileName)
{

	if (datas_.find(fileName) == datas_.end())
	{
		index_++;
		SAnimation::Animation animation = LoadFile(fileName);
		datas_[fileName] = animation;
		datas_[fileName].indexNumber = index_;
		return datas_[fileName].indexNumber;
	}
	else
	{
		return datas_[fileName].indexNumber;
	}

}

void AnimationManager::ApplyAnimation(SAnimation::Skeleton& skeleton, SAnimation::Animation& animation, float time)
{
	for (SAnimation::Joint& joint : skeleton.joints) {
		if (auto it = animation.NodeAnimation.find(joint.name); it != animation.NodeAnimation.end())
		{
			const SAnimation::NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.translate = CalculateValue(rootNodeAnimation.translate.keyframes, time);

			joint.transform.quaternion = CalculateValue(rootNodeAnimation.rotate.keyframes, time);

			joint.transform.scale = CalculateValue(rootNodeAnimation.scale.keyframes, time);

		}
	}
}



void AnimationManager::BlendAnimations(SAnimation::Skeleton& skeleton, const SAnimation::Animation& animationA, const SAnimation::Animation& animationB, const float& blendFactors, SAnimation::Animation& outResult)
{
	
	const size_t animSize = 2;
	outResult;

	//結果
	
	for (auto& joint : skeleton.joints)
	{
		for (size_t index = 0; index < animSize; index++)
		{
			TransformQua blendedTransform{};

			// アニメーションAのジョイントデータを取得
			auto itA = animationA.NodeAnimation.find(joint.name);
			// アニメーションBのジョイントデータを取得
			auto itB = animationB.NodeAnimation.find(joint.name);

			if (itA != animationA.NodeAnimation.end() && itB != animationB.NodeAnimation.end())
			{
				// 両方のアニメーションにジョイントが存在する場合
				const SAnimation::NodeAnimation& nodeA = itA->second;
				const SAnimation::NodeAnimation& nodeB = itB->second;

				TransformQua transformA{}, transformB{}, result{};
				transformA.translate = (*nodeA.translate.keyframes.rbegin()).value;
				transformB.translate= (*nodeB.translate.keyframes.rbegin()).value;
				transformA.scale = (*nodeA.scale.keyframes.rbegin()).value;
				transformB.scale = (*nodeB.scale.keyframes.rbegin()).value;
				transformA.quaternion = (*nodeA.rotate.keyframes.rbegin()).value;
				transformB.quaternion = (*nodeB.rotate.keyframes.rbegin()).value;

				result.scale = Math::Vector::Lerp(transformA.scale, transformB.scale,blendFactors);
				result.quaternion = Math::Qua::Slerp(transformA.quaternion, transformB.quaternion, blendFactors);
				result.translate = Math::Vector::Lerp(transformA.translate, transformB.translate, blendFactors);

				joint.transform.scale = result.scale;
				joint.transform.rotate = result.rotate;
				joint.transform.translate = result.translate;

			}
		}
	}
}

SAnimation::Animation AnimationManager::GetData(const string& fileName)
{
	return datas_[fileName];
}

SAnimation::Animation AnimationManager::GetData(const uint32_t& handle)
{
	for (auto& data : datas_)
	{
		auto& it = data.second;
		if (it.indexNumber == handle)
		{
			return it;
		}
	}
	return {};
}

SAnimation::Animation AnimationManager::LoadFile(const string& filename)
{
	SAnimation::Animation result = {};

	Assimp::Importer importer;
	string file("Resources/Models/" + filename + "/" + filename + ".gltf");
	const aiScene* scene = importer.ReadFile(file.c_str(), 0);
	assert(scene->mNumAnimations != 0);
	aiAnimation* animationAssimp = scene->mAnimations[0];
	result.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);
	//NodeAnimationの情報を入手
	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex)
	{
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];
		SAnimation::NodeAnimation& nodeAnim = result.NodeAnimation[nodeAnimationAssimp->mNodeName.C_Str()];
		//pos解析
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex)
		{
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];
			SAnimation::KeyframeVector3 keyFlame;
			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyFlame.value = { -keyAssimp.mValue.x,keyAssimp.mValue.y, keyAssimp.mValue.z, };
			nodeAnim.translate.keyframes.push_back(keyFlame);
		}
		//Rotate解析
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex)
		{
			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];
			SAnimation::KeyframeQuaternion keyFlame;
			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyFlame.value = { keyAssimp.mValue.x,-keyAssimp.mValue.y,-keyAssimp.mValue.z,keyAssimp.mValue.w };
			nodeAnim.rotate.keyframes.push_back(keyFlame);
		}
		//scale解析
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; ++keyIndex)
		{
			aiVectorKey keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];
			SAnimation::KeyframeVector3 keyFlame;
			keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyFlame.value = { keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z, };
			nodeAnim.scale.keyframes.push_back(keyFlame);
		}
	}

	return result;
}

Vector3 AnimationManager::CalculateValue(const std::vector<SAnimation::KeyframeVector3>& keyflames, float time)
{
	assert(!keyflames.empty());
	if (keyflames.size() == 1 || time <= keyflames[0].time)
	{
		return keyflames[0].value;
	}

	for (size_t index = 0; index < keyflames.size() - 1; ++index)
	{
		size_t nextIndex = index + 1;
		if (keyflames[index].time <= time && time <= keyflames[nextIndex].time)
		{
			float t = (time - keyflames[index].time) / (keyflames[nextIndex].time - keyflames[index].time);
			return Lerp(keyflames[index].value, keyflames[nextIndex].value, t);

		}
	}
	return (*keyflames.rbegin()).value;
}

Quaternion AnimationManager::CalculateValue(const std::vector<SAnimation::KeyframeQuaternion>& keyflames, float time)
{
	assert(!keyflames.empty());
	if (keyflames.size() == 1 || time <= keyflames[0].time)
	{
		return keyflames[0].value;
	}

	for (size_t index = 0; index < keyflames.size() - 1; ++index)
	{
		size_t nextIndex = index + 1;
		if (keyflames[index].time <= time && time <= keyflames[nextIndex].time)
		{
			float t = (time - keyflames[index].time) / (keyflames[nextIndex].time - keyflames[index].time);
			return Math::Qua::Slerp(keyflames[index].value, keyflames[nextIndex].value, t);

		}
	}
	return (*keyflames.rbegin()).value;
}
