#pragma once
#include"Model.h"


class Rect :public Model
{
public:

	Rect();
	~Rect();

	void BufferCreate(RectBufferResource &vartex);

	void Draw(Vec4 leftTop, Vec4 rightTop, Vec4 leftDown, Vec4 rightDown,RectBufferResource vertex);

private:

};

//cleyera//クレイラ
//CLEYERA ENGINE