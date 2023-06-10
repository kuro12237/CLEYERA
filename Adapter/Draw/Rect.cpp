#include "Rect.h"

Rect::Rect()
{
}

Rect::~Rect()
{
}

void Rect::CreateVertex(RectVertexProrertys &vartex)
{
	Model::CreateVertex(vartex.left);
	Model::CreateVertex(vartex.right);

}

void Rect::Draw(Vector4 lefttop,Vector4 righttop,Vector4 leftdown,Vector4 rightDown, RectVertexProrertys vertex)
{

	Model::Draw(lefttop, leftdown, righttop, vertex.left);
	Model::Draw(righttop, leftdown, rightDown, vertex.right);

}


