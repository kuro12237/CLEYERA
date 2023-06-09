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

void Rect::Draw(Vec4 lefttop,Vec4 righttop,Vec4 leftdown,Vec4 rightDown, RectVertexProrertys vertex)
{

	Model::Draw(lefttop, leftdown, righttop, vertex.left);
	Model::Draw(righttop, leftdown, rightDown, vertex.right);

}


