#include"Graphics/DescripterManager/DescriptorManager.h"

struct  TexData
{
	uint32_t index;
	ComPtr<ID3D12Resource> resource;
	Vector2 size;
};

class TexDataResource
{
public:
	TexDataResource(string filePath, TexData texData);
	~TexDataResource();

	uint32_t GetTexHandle() { return texData_.index; }
	void texRelease() { texData_.resource.Reset(); }
	Vector2 GetSize() { return texData_.size; }

private:

	string filePath_;
	TexData texData_;
};
