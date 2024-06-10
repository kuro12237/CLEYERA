#include "TestCharacter.h"

void TestCharacter::Initialize()
{
	name_ = "Player";
}

void TestCharacter::Update()
{
	worldTransform_.UpdateMatrix();
}

void TestCharacter::Draw()
{
	gameObject_->Draw(worldTransform_);
}
