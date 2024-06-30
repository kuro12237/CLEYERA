#pragma once
#include"ISpriteState.h"
#include"CreateResource.h"
#include"Sprite/Sprite.h"
#include"GraphicsPipelineManager.h"
#include"ShaderManager.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Utility/CameraManager/CameraManager.h"

class SpriteBoxState:public ISpriteState
{
public:
	SpriteBoxState() {};
	~SpriteBoxState() {};

	void Initialize(Sprite* state)override;
	void Draw(Sprite* state, WorldTransform worldTransform)override;

private:

	SPSOProperty Get2dSpritePipeline(Sprite* state);

	void CommandCall(uint32_t texHandle,Sprite* state,WorldTransform worldTransform);

	ResourcePeroperty resource_ = {};

	const uint32_t VertexSize = 4;
	const uint32_t IndexSize = 6;

};

