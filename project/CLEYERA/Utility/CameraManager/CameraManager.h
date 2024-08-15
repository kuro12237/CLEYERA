#pragma once
#include"Pch.h"
#include"CameraData.h"


class CameraManager
{
public:

	static CameraManager* GetInstance();

	void Initialize();

	void Update();

	void CommandCall(uint32_t num);

	void ResetCamera(const CameraData& camera);

#pragma region Get

	const CameraData* GetCameraData() { return cameraData_; }

#pragma endregion


private:

	const CameraData* cameraData_ = nullptr;

	CameraManager() = default;
	~CameraManager() = default;
	CameraManager(const CameraManager&) = delete;
	const CameraManager& operator=(const 	CameraManager&) = delete;
};
