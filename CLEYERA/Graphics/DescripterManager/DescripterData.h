#pragma once
#include"DirectXCommon.h"
#include"BufferResources.h"

class DescripterData
{
public:
	DescripterData(const uint32_t& Index, const string& name)
	{
		this->index = Index;
		this->name=name;
	};
	~DescripterData() {};

	uint32_t GetIndex() { return index; }
	string GetName() { return name; }

	void SetBuffer()

private:

	string name = {};
	uint32_t index = 0;

};
