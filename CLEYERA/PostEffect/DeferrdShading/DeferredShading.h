#pragma once
#include"DirectXCommon.h"
#include"CameraData.h"
#include"WorldTransform.h"
#include"GraphicsPipelineManager.h"
#include"Light/LightingManager.h"
#include"Light/DirectionLIght.h"

struct MaterialDefferdShading
{
	Vector4 color;
	float shininess;
};

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

	void PrePosDraw();

	void PostPosDraw();


	void PreDepthDraw();

	void PostDepthDraw();

	void Draw(const CameraData& camera);

private:

	void ColorBufferUpdate();

	void CommandCallView(const float& width, const float& height);
	void CommandCallScissor();

	void CreateTexBuffer();



	unique_ptr<BufferResource<uint32_t>>colorTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>normalTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>depthBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>depthTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>PosTexBuffer_ = nullptr;


	unique_ptr<BufferResource<VertexData>>vertexBuffer_ = nullptr;
	vector<VertexData>vertexData_;

	unique_ptr<BufferResource<uint32_t>>indexBuffer_ = nullptr;
	vector<uint32_t>indexData_{};

	unique_ptr<BufferResource<MaterialDefferdShading>>materialBuffer_ = nullptr;
	MaterialDefferdShading materialData = {};

	unique_ptr<BufferResource<TransformationMatrix>>wvp_ = nullptr;
	TransformationMatrix matrixData_{};
};