#include "CameraManager.h"

using namespace Engine::Manager;
using namespace Engine::Camera;


CameraManager* CameraManager::GetInstance()
{
	static CameraManager instance;
	return &instance;
}

void CameraManager::Initialize()
{
	cameraData_ = nullptr;
}

void CameraManager::Update()
{

}

void CameraManager::PsCommandCall(const uint32_t& num)
{
	cameraData_->psBuffer_->CommandCall(num);
}

void CameraManager::VsCommandCall(const uint32_t &num)
{
	cameraData_->buffer_->CommandCall(num);
}

void CameraManager::ResetCamera(const CameraData& camera)
{
	cameraData_ = nullptr;
	cameraData_ = &camera;
}
