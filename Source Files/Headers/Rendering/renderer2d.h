#pragma once
#include "graphics.h"
#include "renderable2D.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

class Renderer2D
{
public:
	Renderer2D(Graphics& gfx);
	void Submit(std::shared_ptr<Renderable2D> obj);
	void Flush();
	void Shutdown();

	VertexData* vData;
	unsigned short* iData;

	int vDataSize;
	int indexCount;

	Graphics& gfx;
	std::vector<std::shared_ptr<Renderable2D>> renderables;

	std::unique_ptr<VertexConstant> vconst;
};
