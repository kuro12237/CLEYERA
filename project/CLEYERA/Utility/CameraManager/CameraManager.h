#pragma once
#include"Pch.h"
#include"CameraData.h"

namespace Engine::Manager
{
	using namespace Engine::Camera;

	/// <summary>
	/// �J�����Ǘ��N���X�J���������̃N���X�ɐݒ肷��
	/// </summary>
	class CameraManager
	{
	public:

		static CameraManager* GetInstance();

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

	
		/// <summary>
		/// �J�������Z�b�g
		/// </summary>
		/// <param name="camera"></param>
		void ResetCamera(const CameraData& camera);

#pragma region Get
		const CameraData* GetCameraData() { return cameraData_; }
#pragma endregion

		/// <summary>
		/// �g�p���Ȃ�
		/// </summary>
		/// <param name="num"></param>
		void PsCommandCall(const uint32_t& num);

		/// <summary>
		/// �g�p���Ȃ�
		/// </summary>
		/// <param name="num"></param>
		void VsCommandCall(const uint32_t& num);

	private:

		const CameraData* cameraData_ = nullptr;

		CameraManager() = default;
		~CameraManager() = default;
		CameraManager(const CameraManager&) = delete;
		const CameraManager& operator=(const 	CameraManager&) = delete;
	};
}