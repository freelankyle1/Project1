#pragma once
#include "renderable2d.h"
#include "globals.h"

class Quad2D : public Renderable2D
{
public:
	Quad2D(Graphics& gfxDevice, const VertexData* vData);
	~Quad2D() override;
	VertexData* GetVertexData() const override;
	virtual unsigned int GetVertexCount() const override;
	virtual unsigned short* GetIndices() const override;
	virtual unsigned int GetIndexCount() const override;
	
	VertexData* PerVertex;
	//unsigned short* indices;
	unsigned short* indices;
};