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
	void Bind(Graphics& gfx) const override;
	void AddBind(std::shared_ptr<Bindable> bind) override;
	void AddIndexBuffer(std::shared_ptr<IndexBuffer> ib);
	DirectX::XMMATRIX GetTransform(Graphics& gfx) override;
	UINT GetIndexCount() const override;
	void Update(Graphics& gfx, float xx, float yy, float dt) override;
	VertexData* GetVertexData() const override;
	virtual unsigned short* GetIndices() const override;
	virtual unsigned int GetVertexCount() const override;
	void Cleanup() override;




	float rotationY = 0.0f;
	float rotationX = 0.0f;
	float rotationZ = 0.0f;

	float translationX;
	float translationY;
	float translationZ = 5.0f;

	static bool staticInit;
	static UINT indexCount;

	VertexData* PerVertex;
	unsigned short* indices;
	unsigned int VertexCount;


};