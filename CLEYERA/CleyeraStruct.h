#pragma once
#include"Vector/Vector4.h"
#include<windows.h>
#include<string>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

#include<cassert>



enum Color
{
	RED =  0xFF0000FF,
	GREEN= 0x00FF00FF,
	BLUE = 0x0000FFFF,
	WHITE= 0xFFFFFFFF,
	BLACK= 0x000000FF
};


struct  BufferResource
{
	D3D12_VERTEX_BUFFER_VIEW BufferView;
	ID3D12Resource* Vertex;
	ID3D12Resource* Material;
};

struct RectBufferResource
{
	BufferResource left;
	BufferResource right;

};
struct Commands
{
	//コマンドキュー
	ID3D12CommandQueue* Queue;
	D3D12_COMMAND_QUEUE_DESC QueueDesc{};
	//コマンドアローケータ
	ID3D12CommandAllocator* Allocator;
	//コマンドリスト
	ID3D12GraphicsCommandList* List;
};
