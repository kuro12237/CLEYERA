#pragma once
#include"SAnimation.h"

class AnimationManager
{
public:

	static AnimationManager* GetInstance();

	uint32_t LoadAnimation(const string& fileName);

private:

	SAnimation::Animation LoadFile(const string& filename);

	uint32_t index_ = 0;
	std::map<std::string, SAnimation::Animation>datas_;

#pragma region 
	//Singleton
	AnimationManager() = default;
	~AnimationManager()  = default;
	AnimationManager(const AnimationManager&) = delete;
	const AnimationManager& operator=(const AnimationManager&) = delete;
#pragma endregion 
};