#pragma once
#include"Model.h"


class Rect :public Model
{
public:

	Rect();
	~Rect();

	void BufferCreate(RectBufferResource &vartex);

	void Draw(Vector4 leftTop, Vector4 rightTop, Vector4 leftDown, Vector4 rightDown, unsigned int ColorCode, Matrix4x4 matrixTransform, RectBufferResource vertex);

private:

};

//cleyera//クレイラ
//CLEYERA ENGINE