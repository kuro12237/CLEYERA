#pragma once
#include"ModelManager.h"
#include"Model/primitive/Line.h"

enum PrimitiveType
{
	SPHERE,
	BOX
};

class IParticleEmitDraw
{
public:
	IParticleEmitDraw() = default;
	virtual~IParticleEmitDraw() {};

	void Create(PrimitiveType type);

	void Update();

	void Draw(const WorldTransform& w);

private:

	void CreateSphereVertex();

	vector<unique_ptr<LineModel>>lines_ = {};
};