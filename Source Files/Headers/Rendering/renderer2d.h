#pragma once
#include "graphics.h"
#include "renderable2D.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

#define MAX_VERTEX_COUNT 50000
#define MAX_INDEX_BYTE_COUNT MAX_VERTEX_COUNT * 3 //for triangles
#define MAX_VERTEX_BYTE_COUNT MAX_VERTEX_COUNT * 3

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
