#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ColorConverter/ColorConverter.h"

class ChangeSceneAnimation
{
public:

	static ChangeSceneAnimation* GetInstance();

	void Initialize();

	void Update();

	void Draw();

	void ChangeStart();
	 
#pragma region Get

	bool GetEnd() { return isEndFlag_; }

	bool GetIsComplite() { return isCompliteFlag_; }
	bool GetIsChangeSceneFlag() { return isChangeSceneFlag_; }

#pragma endregion


private:

	bool isEndFlag_ = false;
	bool isStartFlag_ = false;
	bool isCompliteFlag_ = true;

	bool isChangeSceneFlag_ = false;

	bool isUpdateFlag_ = false;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform wT_ = {};

	Math::Vector::Vector2 center_ = {};

	float flame_ = 0.0f;
	float flameMax_ = 120.0f;

	float dissolveMax = 1.0f;
	const uint32_t edgeColor_16 = 0xFFFFFFFF;

	uint32_t tex_ = 0;
	vector<uint32_t>noiseTex_ = {};

	//Singleton
	ChangeSceneAnimation() = default;
	~ChangeSceneAnimation() = default;
	ChangeSceneAnimation(const  ChangeSceneAnimation&) = delete;
	const  ChangeSceneAnimation& operator=(const  ChangeSceneAnimation&) = delete;
};
