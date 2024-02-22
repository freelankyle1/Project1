#include "Headers/pch.h"
#include "Headers/Rendering/vertexconstants.h"
#include "Headers/asserts.h"

VertexConstant::VertexConstant(Graphics& gfx)
	:gfx(gfx)
{}

VertexConstant::VertexConstant(Graphics& gfx, ConstantBuffer& constBuffer)
	:gfx(gfx)
{
	D3D11_BUFFER_DESC bd = {};
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.MiscFlags = 0u;
	bd.StructureByteStride = 0u;
	bd.ByteWidth = sizeof(constBuffer);

	D3D11_SUBRESOURCE_DATA sr = {};
	sr.pSysMem = &constBuffer;

	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&bd, &sr, &m_pBuffer);
	ASSERT(hr, "failed to create vertex constant buffer!");
}

void VertexConstant::Initialize(ConstantBuffer& constBuffer)
{
	D3D11_BUFFER_DESC bd = {};
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.MiscFlags = 0u;
	bd.StructureByteStride = 0u;
	bd.ByteWidth = sizeof(constBuffer);

	D3D11_SUBRESOURCE_DATA sr = {};
	sr.pSysMem = &constBuffer;

	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&bd, &sr, &m_pBuffer);
	ASSERT(hr, "failed to create vertex constant buffer!");
}

void VertexConstant::Bind(Graphics& gfxDevice)
{
	gfx.GetContext()->VSSetConstantBuffers(0u, 1u, m_pBuffer.GetAddressOf());
}

void VertexConstant::UpdateConstant(ConstantBuffer& cb)
{
	using namespace DirectX;
	D3D11_MAPPED_SUBRESOURCE msr;

	gfx.GetContext()->Map(m_pBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
	memcpy(msr.pData, &cb, sizeof(cb));
	gfx.GetContext()->Unmap(m_pBuffer.Get(), 0u);
}