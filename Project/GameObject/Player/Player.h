#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"

#include"command/PlayerCommandHandler.h"

#include"state/IPlayerState.h"
#include"state/PlayerStateNone.h"

class Player :public IObjectData, public ICollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void OnCollision(ICollider* c)override;

	void ChangeState(unique_ptr<IPlayerState>newState);

#pragma region Command

	void Jamp();

	void Move();

#pragma endregion

private:

	unique_ptr<IPlayerState>state_ = nullptr;

	bool isJamp_ = false;;

};
