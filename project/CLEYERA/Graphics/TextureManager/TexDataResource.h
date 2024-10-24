#include"Graphics/DescripterManager/DescriptorManager.h"


struct  TexData
{
	uint32_t index;
	ComPtr<ID3D12Resource> resource;
	Math::Vector::Vector2 size;
};

/// <summary>
/// テクスチャ保存クラス
/// </summary>
class TexDataResource
{
public:
	TexDataResource(string filePath, TexData texData);
	~TexDataResource();

	/// <summary>
	/// 解放
	/// </summary>
	void texRelease() { texData_.resource.Reset(); }

#pragma region Get
	uint32_t GetTexHandle() { return texData_.index; }
	Math::Vector::Vector2 GetSize() { return texData_.size; }
#pragma endregion

private:

	string filePath_;
	TexData texData_;
};
