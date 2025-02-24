#include "EndAnimation.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void EndAnimation::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	postEffect_ = PostEffect::GetInstance();


}

void EndAnimation::Update()
{
   this->isComplete_ = true;
}

void EndAnimation::Draw2d()
{
}
