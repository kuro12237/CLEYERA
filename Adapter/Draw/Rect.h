#pragma once
#include"Model.h"


class Rect :public Model
{
public:

	Rect();
	~Rect();

	void CreateVertex(RectVertexProrertys &vartex);

	void Draw(Vector4 leftTop, Vector4 rightTop, Vector4 leftDown, Vector4 rightDown,RectVertexProrertys vertex);

private:

};

//cleyera//クレイラ
//CLEYERA ENGINE