#pragma once
#include"../CleyeraStruct.h"

#include<windows.h>
#include<string>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>


#include<cassert>

#include "../Setup/DirectXSetup.h"

#include "../Matrix/MatrixTransform.h"
#include"../Vector/VectorTransform.h"

class  Model
{
public:
	 Model();
	~ Model();

	void DirectXSetDevice(ID3D12Device* device_);

	void DirectXSetCommands(Commands commands_);


	static BufferResource CreateBufferResource(ID3D12Device* device, size_t sizeInbyte);

	void CreateVertex(BufferResource &vertex);

	void Draw(Vector4 top, Vector4 left, Vector4 right, BufferResource &vertex);

	void VartexRelease(BufferResource vartex);

private:


	MatrixTransform* matrixTransform_ = nullptr;
	VectorTransform* vectorTransform_ = nullptr;

	ID3D12Device* device = nullptr;
	Commands commands;
	HRESULT hr;

};


