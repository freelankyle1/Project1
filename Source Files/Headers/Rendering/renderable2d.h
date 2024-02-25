#pragma once

#include "bindable.h"
#include "graphics.h"
#include "vertexconstants.h"


class Renderable2D
{
public:
	virtual ~Renderable2D() = default;
	virtual VertexData* GetVertexData() const = 0;
	virtual unsigned int GetVertexCount() const = 0;
	virtual unsigned short* GetIndices() const = 0;
	virtual unsigned int GetIndexCount() const = 0;

};

