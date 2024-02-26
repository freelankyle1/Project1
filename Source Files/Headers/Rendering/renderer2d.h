#pragma once
#include "graphics.h"
#include "renderable2D.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

#define MAX_PRIMITVE_COUNT 10000
#define MAX_VERTEX_COUNT MAX_PRIMITVE_COUNT * 4 //for quads
#define MAX_INDEX_COUNT MAX_PRIMITVE_COUNT  * 6


struct RendererStats
{
	int TotalVertices = 0;
	int DrawCalls = 0;
};

class Renderer2D
{
public:
	Renderer2D(Graphics& gfx);
	void BeginScene();
	void Submit(std::shared_ptr<Renderable2D> obj);
	void StartBatch();
	void Flush();
	void Update(float transX, float transY, float transZ);
	void EndScene();
	void Shutdown();

	VertexData* vData;
	unsigned short* iData;

	int vDataSize;
	int indexCount;

	Graphics& gfx;
	std::unique_ptr<VertexConstant> vConst;
	
	const RendererStats& GetStats();
	void EndStats();
	RendererStats stats;
};
