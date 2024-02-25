#pragma once
#include "graphics.h"
#include "renderable2D.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

#define MAX_PRIMITVE_COUNT 90000
#define MAX_VERTEX_COUNT MAX_PRIMITVE_COUNT * 4 //for quads
#define MAX_INDEX_COUNT MAX_PRIMITVE_COUNT  * 6

class Renderer2D
{
public:
	Renderer2D(Graphics& gfx);
	void Submit(std::shared_ptr<Renderable2D> obj);
	void StartBatch();
	void Flush();
	void Update(float transX, float transY, float transZ);
	int GetVertexAmount() const;
	void Shutdown();

	VertexData* vData;
	unsigned short* iData;

	int vDataSize;
	int indexCount;

	Graphics& gfx;
	std::unique_ptr<VertexConstant> vConst;
};
