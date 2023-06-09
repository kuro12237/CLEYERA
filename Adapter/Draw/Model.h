#pragma once
#include"../Struct.h"

#include<windows.h>
#include<string>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>


#include<cassert>

#include "../Setup/DirectXSetup.h"

class  Model
{
public:
	 Model();
	~ Model();

	void DirectXSetDevice(ID3D12Device* device_);

	void DirectXSetCommands(Commands commands_);

	void CreateVertex(VertexProperty &vertex);

	void Draw(Vec4 top, Vec4 left, Vec4 right, VertexProperty &vertex);

	void VartexRelease(VertexProperty vartex);

private:

	ID3D12Device* device = nullptr;

	Commands commands;

	HRESULT hr;

};


