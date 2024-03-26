#pragma once
#include"DirectXCommon.h"
#include"CameraData.h"
#include"WorldTransform.h"

class DefferredShading
{
public:
	DefferredShading() {};
	~DefferredShading() {};

	void Initialize();

	void PreColorDraw();

	void PostColorDraw();

	void PreNormalDraw();

	void PostNormalDraw();

	void Draw(const WorldTransform &worldTransform,const CameraData& camera);

private:


	void CommandCallView(const float& width, const float& height);
	void CommandCallScissor();

	void CreateTexBuffer();

	unique_ptr<BufferResource<uint32_t>>colorTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>normalTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>depthBuffer_ = nullptr;

	unique_ptr<BufferResource<VertexData>>vertexBuffer_ = nullptr;
	vector<VertexData>vertexData_;

	unique_ptr<BufferResource<uint32_t>>indexBuffer_ = nullptr;

	unique_ptr<BufferResource<Material>>materialBuffer_ = nullptr;
	Material materialData = {};
};