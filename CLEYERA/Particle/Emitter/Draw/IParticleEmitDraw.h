#pragma once
#include"ModelManager.h"
#include"Model/primitive/LineModel.h"

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

	void Create(PrimitiveType type,string name);

	void Update();

	void Draw(const WorldTransform& w);

private:

	void CreateSphereVertex();

	string name_="";
	vector<unique_ptr<Primitive::LineModel>>lines_ = {};
	unique_ptr<Primitive::LineModel > line_ = nullptr;
};