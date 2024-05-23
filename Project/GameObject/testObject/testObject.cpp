#include "testObject.h"

void testObject::Initialize()
{
	this->SetName("Cube");
	Game3dObjectDesc desc;
	desc.useLight = true;
	ModelManager::LoadObjectFile("DebugTestBox");
	this->GameObjectCreate("DebugTestBox", desc);
	this->WtCreate({ {1,1,1},{},{} }, nullptr);

}

void testObject::Update()
{
	
	this->UpdateMat();
}

void testObject::Draw()
{
	this->DrawObject();
}
