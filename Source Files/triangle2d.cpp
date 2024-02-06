#include "Headers/pch.h"
#include "Headers/Rendering/globals.h"
#include "Headers/Rendering/triangle2d.h"

Triangle2D::Triangle2D(Graphics& gfx)
{
	std::vector<Vertex> vertices =
	{
		{-1.0f,-1.0f, 0.0f},
		{ 1.0f, 1.0f, 0.0f},
		{ 1.0f,-1.0f, 0.0f},
	};
	
	AddBind(std::make_shared<VertexBuffer>(gfx, vertices));

	auto pvs = std::make_shared<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetByteCode();
	AddBind(std::move(pvs));

	AddBind(std::make_shared<PixelShader>(gfx, L"PixelShader.cso"));

	std::vector<USHORT> indices =
	{
		0,1,2,
	};
	
	AddIndexBuffer(std::make_shared<IndexBuffer>(gfx, indices));


	ConstantBuffer2 cb2
	{
		{
			{1.0f,0.0f,1.0f},
		}
	};

	AddBind(std::make_shared<PixelConstant>(gfx, cb2));

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	AddBind(std::make_shared<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_shared<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	
	ConstantBuffer cb;
	cb.transform = GetTransform(gfx);

	std::shared_ptr vcb = std::make_shared<VertexConstant>(gfx, cb);
	m_VcBuffer = vcb.get();
	AddBind(std::move(vcb));

}

void Triangle2D::Bind(Graphics& gfx) const
{
	//loop through our vector of binds and bind everything necessary
	//to draw the primitive
	for(const auto & it : m_Binds)
	{
		it->Bind(gfx);
	}
}

void Triangle2D::AddBind(std::shared_ptr<Bindable> bind)
{
	m_Binds.push_back(std::move(bind));
}

void Triangle2D::AddIndexBuffer(std::shared_ptr<IndexBuffer> ib)
{
	m_IndexCount = ib->GetSize();
	m_Binds.push_back(std::move(ib));
}

DirectX::XMMATRIX Triangle2D::GetTransform(Graphics& gfx)
{
	using namespace DirectX;
	return	XMMatrixRotationZ  (0.0f) *
			XMMatrixRotationY  (0.0f) *
			XMMatrixRotationX  (0.0f) *
			XMMatrixTranslation(0.0f, 0.0f, 5.0f);
}

UINT Triangle2D::GetIndexCount() const
{
	return m_IndexCount;
}

void Triangle2D::Update(Graphics& gfx, float dt)
{
	using namespace DirectX;


	ConstantBuffer cb = {
		XMMatrixTranspose(
		GetTransform(gfx) * gfx.GetProjection())
	};


	m_VcBuffer->UpdateConstant(gfx, cb);
}
