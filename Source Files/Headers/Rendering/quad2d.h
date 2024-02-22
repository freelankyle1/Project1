#pragma once
#include "renderable.h"
#include "globals.h"
#include "vertexconstants.h"

class Quad2D : public Renderable
{
public:
	Quad2D(Graphics& gfxDevice, float translation);
	DirectX::XMMATRIX GetTransform(Graphics& gfx) override;
	int GetVertexCount() const override;
	unsigned short* GetIndices() const;
	VertexData* GetVertices() const;
	~Quad2D();
	void Update(Graphics& gfxDevice) override;

	ConstantBuffer CBuf = {
			DirectX::XMMatrixRotationZ(0.0f) *
			DirectX::XMMatrixRotationX(0.0f) *
			DirectX::XMMatrixRotationY(0.0f) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)
	};

	VertexData* PerVertex;
	unsigned short* indices;

	float translationX = 0.0f;
};