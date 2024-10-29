#pragma once
#include"Utility/SplineMotion/SplineMotion.h"

#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"

/// <summary>
/// �X�^�[�g�̃J�����̓���
/// </summary>
class StartCameraMotion :public IObjectData
{
public:
	StartCameraMotion() {};
	~StartCameraMotion() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="�J�����ԍ�"></param>
	void Initilaize(const uint32_t &index);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �f�o�b�O�p
	/// </summary>
	void DrawLines();

#pragma region Set

	void SetIsStartFlag(const bool& f) { isStartFlag_ = f; }

#pragma endregion


private:

	unique_ptr<SplineMotion>splineMotion_ = nullptr;
	bool isComplete_ = false;
	bool isStartFlag_ = false;

	uint32_t cameraIndex_ = 0;

	RailData railData_ = {};
};
