#pragma once
#include"Sprite/Sprite.h"
#include"Utility/DeltaTimer/DeltaTimer.h"

class PlayerHp
{
public:
	PlayerHp() {};
	~PlayerHp() {};

	void Initialize();

	void Update();

	void Draw2d(const CameraData& camera);

	void subtractHPCount(uint32_t param = 1);

	void ImGuiUpdate();

#pragma region Get

	const uint32_t& GetHp()  { return playerHpCount_; }

#pragma endregion


private:

	static const uint32_t playerHpMax_ = 4;
	uint32_t playerHpCount_ = 0;

	array<WorldTransform,playerHpMax_> worldTransform_;
	unique_ptr<Sprite>sprite_ = nullptr;
	uint32_t spriteHandle_ = 0;


	float flame_ = 0.0f;
	static const uint32_t coolTimerMax_ = 2;
	uint32_t coolTimer_ = 0;

};