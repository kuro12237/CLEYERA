#pragma once
#include"DirectXCommon.h"

class DescripterData
{
public:
	DescripterData(const uint32_t& Index, const string& name)
	{
		this->index = Index;
		this->name=name;
	};
	~DescripterData() {};

	void SetBuf(ComPtr<ID3D12Resource>buf) { buf_ = buf; }

	uint32_t GetIndex() { return index; }
	string GetName() { return name; }
	ComPtr<ID3D12Resource>GetBuf() { return buf_; }

private:

	ComPtr<ID3D12Resource>buf_ = nullptr;
	string name = {};
	uint32_t index = 0;

};
