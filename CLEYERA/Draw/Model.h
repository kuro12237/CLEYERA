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


	static ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInbyte);
	static D3D12_VERTEX_BUFFER_VIEW CreateBufferVier(size_t sizeInbyte ,ID3D12Resource* Resource);


	void CreateVertex(BufferResource &vertex);

	void Draw(Vector4 top, Vector4 left, Vector4 right,unsigned int ColorCode, BufferResource &Resource);

	void VartexRelease(BufferResource Resource);

   /// <summary>
   /// 色16進数からVector4に変換する関数
   /// </summary>
   /// <param name="color"></param>
   /// <returns></returns>
   static Vector4 ColorAdapter(unsigned int color);

private:


	MatrixTransform* matrixTransform_ = nullptr;
	VectorTransform* vectorTransform_ = nullptr;

	ID3D12Device* device = nullptr;
	Commands commands;
	HRESULT hr;

};


