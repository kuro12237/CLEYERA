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

	uint32_t GetTexHandle() { return texData_.index; }
	void texRelease() { texData_.resource.Reset(); }
	Math::Vector::Vector2 GetSize() { return texData_.size; }

private:

	string filePath_;
	TexData texData_;
};
