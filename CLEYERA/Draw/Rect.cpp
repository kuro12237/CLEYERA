#include "Rect.h"

Rect::Rect()
{
}

Rect::~Rect()
{
}

void Rect::BufferCreate(RectBufferResource &vartex)
{
	Model::CreateVertex(vartex.left);
	Model::CreateVertex(vartex.right);
	
}

void Rect::Draw(Vector4 lefttop,Vector4 righttop,Vector4 leftdown,Vector4 rightDown, unsigned int ColorCode, RectBufferResource vertex)
{

	Model::Draw(lefttop, leftdown, righttop,ColorCode, vertex.left);
	Model::Draw(righttop, leftdown, rightDown,ColorCode, vertex.right);

}


