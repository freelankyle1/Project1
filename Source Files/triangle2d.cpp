#include "Headers/pch.h"
#include "Headers/Rendering/globals.h"
#include "Headers/Rendering/triangle2d.h"


Triangle2D::Triangle2D(Graphics& gfx, const VertexData* vData)
{
	PerVertex = new VertexData[3];
	indices = new unsigned short[3];

	for (int i = 0; i < 3; i++)
	{
		PerVertex[i].pos = vData[i].pos;
		//PerVertex[i].col = vData[i].col;


		indices[i] = i;
	}
}

Triangle2D::~Triangle2D()
{
	delete[] PerVertex;
	delete[] indices;
}

VertexData* Triangle2D::GetVertexData() const
{
	return PerVertex;
}

unsigned int Triangle2D::GetVertexCount() const
{
	return 3;
}

unsigned short* Triangle2D::GetIndices() const
{
	return indices;
}

unsigned int Triangle2D::GetIndexCount() const
{
	return 3;
}




