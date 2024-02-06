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
	Triangle2D(Graphics& gfx);
	void Bind(Graphics& gfx) const override;
	void AddBind(std::shared_ptr<Bindable> bind) override;
	void AddIndexBuffer(std::shared_ptr<IndexBuffer> ib);
	DirectX::XMMATRIX GetTransform(Graphics& gfx) override;
	UINT GetIndexCount() const override;
	void Update(Graphics& gfx, float dt) override;



	//uint indexcount m_IndexCount
	//vector of binds m_Binds

};