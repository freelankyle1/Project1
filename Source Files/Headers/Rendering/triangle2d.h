#pragma once
#include "renderable2d.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexconstants.h"
#include "pixelconstants.h"
#include "shader.h"
#include "inputlayout.h"
#include "topology.h"

class Triangle2D : public Renderable2D
{
public:
	Triangle2D(Graphics& gfx, const VertexData* vData);
	~Triangle2D() override;
	VertexData* GetVertexData() const override;
	virtual unsigned int GetVertexCount() const override;
	virtual unsigned short* GetIndices() const override;
	unsigned int GetIndexCount() const override;

	VertexData* PerVertex;
	unsigned short* indices;

};