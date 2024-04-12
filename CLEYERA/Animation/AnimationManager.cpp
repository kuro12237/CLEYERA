#include "AnimationManager.h"

uint32_t AnimationManager::LoadAnimation(const string& fileName)
{
    index_++;

    SAnimation::Animation animation = LoadFile(fileName);

    return index_;
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
            nodeAnim.translate.push_back(keyFlame);
        }
        //Rotate解析
        for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex)
        {
            aiQuaternion& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];

        }
    }

    return result;
}
