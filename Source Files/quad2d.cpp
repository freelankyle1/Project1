#include "Headers/pch.h"

#include "Headers/Rendering/quad2d.h"


Quad2D::Quad2D(Graphics& gfxDevice, const VertexData* vData)
{
	PerVertex = new VertexData[4];
	indices = new unsigned short[6];

	for (int i = 0; i < 4; i++)
	{
		PerVertex[i].pos = vData[i].pos;
		PerVertex[i].col = vData[i].col;
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 1;
}

Quad2D::~Quad2D()
{
	delete[] PerVertex;
	delete[] indices;
}


VertexData* Quad2D::GetVertexData() const
{
	return PerVertex;
}
unsigned int Quad2D::GetVertexCount() const
{
	return 4;
}

unsigned short* Quad2D::GetIndices() const
{
	return indices;
}

unsigned int Quad2D::GetIndexCount() const
{
	return 6;
}
