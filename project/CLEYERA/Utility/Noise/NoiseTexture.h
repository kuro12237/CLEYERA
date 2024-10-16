#pragma once
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// �m�C�Y�p�̃e�N�X�`��
/// </summary>
class NoiseTexture
{
public:

	static NoiseTexture* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

#pragma region Get

	uint32_t GetIndex() { return index_; }

#pragma endregion

�@///�g�p���Ȃ�
	void RootParamerter();
private:

	string name = "Resources/Default/noise.png";
	uint32_t index_ = 0;

	NoiseTexture() = default;
	~NoiseTexture() = default;
	NoiseTexture(const NoiseTexture&) = delete;
	const NoiseTexture& operator=(const 	NoiseTexture&) = delete;
};