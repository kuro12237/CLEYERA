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

	void Create(PrimitiveType type,string name);

	void Update();

	void Draw(const WorldTransform& w);

private:

	void CreateSphereVertex();

	string name_="";
	vector<unique_ptr<LineModel>>lines_ = {};
	unique_ptr<LineModel > line_ = nullptr;
};