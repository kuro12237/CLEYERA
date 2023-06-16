#pragma once
#include <combaseapi.h>
#include"CLEYERA/externals/DirectXTex/DirectXTex/DirectXTexP.h"
#

class TexManager
{
public:
	TexManager();
	~TexManager();

	void Initialize();

	DirectX::ScratchImage Load(const std::strings);

	void EndFlame();

private:

};

