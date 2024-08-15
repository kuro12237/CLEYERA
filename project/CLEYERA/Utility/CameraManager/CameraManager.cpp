#include "CameraManager.h"

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

void CameraManager::CommandCall(uint32_t num)
{
	cameraData_->buffer_->CommandCall(num);
}

void CameraManager::ResetCamera(const CameraData& camera)
{
	cameraData_ = nullptr;
	cameraData_ = &camera;
}
