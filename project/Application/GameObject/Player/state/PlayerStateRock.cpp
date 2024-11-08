#include "PlayerStateRock.h"

void PlayerStateRock::Initialize(Player* p)
{
	p;
	gameInst = GameObjectManager::GetInstance();

	Game3dObjectDesc desc;
	desc.colorDesc.grayFactor_ = 1.0f;
	gameInst->GetObj3dData(p->INameable::GetName())->SetGameObjeDesc(desc);
}

void PlayerStateRock::Update(Player* p)
{
	timer_ += DeltaTimer(flame_);
	if (timer_ >= MaxTimer_)
	{
		Game3dObjectDesc desc;
		desc.colorDesc.grayFactor_ = 0.0f;
		gameInst->GetObj3dData(p->INameable::GetName())->SetGameObjeDesc(desc);

		p->MarkStateForRemoval<PlayerStateRock>();
	}
}
