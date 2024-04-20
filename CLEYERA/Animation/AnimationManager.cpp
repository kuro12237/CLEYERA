#include "AnimationManager.h"

using namespace Math::Vector;
using namespace Math::Matrix;
using namespace Math::Qua;

AnimationManager* AnimationManager::GetInstance()
{
    static AnimationManager instance;
    return &instance;
}

uint32_t AnimationManager::LoadAnimation(const string& fileName)
{
    index_++;

    SAnimation::Animation animation = LoadFile(fileName);
    datas_[fileName] = animation;

    return index_;
}

void AnimationManager::ApplyAnimation(SAnimation::Skeleton& skeleton, SAnimation::Animation& animation, float time)
{
    for (SAnimation::Joint& joint : skeleton.joints) {
        if (auto it=animation.NodeAnimation.find(joint.name); it!=animation.NodeAnimation.end())
        {
            const SAnimation::NodeAnimation& rootNodeAnimation = (*it).second;
            joint.transform.translate = CalculateValue(rootNodeAnimation.translate.keyframes, time);

            joint.transform.quaternion = CalculateValue(rootNodeAnimation.rotate.keyframes, time);

            joint.transform.scale = CalculateValue(rootNodeAnimation.scale.keyframes, time);
           
            

        }
    }
}

SAnimation::Animation AnimationManager::GetData(const string& fileName)
{
    return datas_[fileName];
}

SAnimation::Animation AnimationManager::LoadFile(const string& filename)
{
    SAnimation::Animation result = {};

    Assimp::Importer importer;
    string file("Resources/Models/" + filename + "/" + filename + ".gltf");
    const aiScene* scene = importer.ReadFile(file.c_str(), 0);
    assert(scene->mNumAnimations !=0);
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
        for (uint32_t keyIndex = 0;  keyIndex < nodeAnimationAssimp->mNumScalingKeys;  ++keyIndex)
        {
            aiVectorKey keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];
            SAnimation::KeyframeVector3 keyFlame;
            keyFlame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
            keyFlame.value = { keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z,};
            nodeAnim.scale.keyframes.push_back(keyFlame);
        }
    }

    return result;
}

Vector3 AnimationManager::CalculateValue(const std::vector<SAnimation::KeyframeVector3>& keyflames, float time)
{
    //assert(!keyflames.empty());
    if (keyflames.size()==1||time<=keyflames[0].time)
    {
        return keyflames[0].value;
    }

    for (size_t index = 0; index < keyflames.size() - 1; ++index)
    {
        size_t nextIndex = index +1;
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
