#include "Headers/pch.h"
#include "Headers/Rendering/buffers.h"
#include "Headers/graphics.h"
#include "Headers/asserts.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>& buffer)
{
	m_Stride = sizeof(Vertex);
	m_Offset = 0u;
	m_VertexBuffer = std::move(buffer);

	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = m_VertexBuffer.size() * sizeof(Vertex);
	m_BufferDesc.StructureByteStride = sizeof(Vertex);

	m_SubresourceData.pSysMem = m_VertexBuffer.data();
}

void VertexBuffer::CreateBuffer(const Graphics& gfx)
{
	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create vertex buffer!");
}

void VertexBuffer::Bind(const Graphics& gfx)
{
	gfx.GetContext()->IASetVertexBuffers(0u, 1u, m_pBuffer.GetAddressOf(), &m_Stride, &m_Offset);
}


IndexBuffer::IndexBuffer(std::vector<USHORT>& buffer)
{
	m_IndexBuffer = std::move(buffer);

	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.CPUAccessFlags = 0u;
	m_BufferDesc.MiscFlags = 0u;
	m_BufferDesc.ByteWidth = m_IndexBuffer.size() * sizeof(USHORT);
	m_BufferDesc.StructureByteStride = sizeof(USHORT);
	
	m_SubresourceData.pSysMem = m_IndexBuffer.data();
}

void IndexBuffer::CreateBuffer(const Graphics& gfx)
{
	HRESULT hr;
	hr = gfx.GetDevice()->CreateBuffer(&m_BufferDesc, &m_SubresourceData, &m_pBuffer);
	ASSERT(hr, "failed to create index buffer!");
}

void IndexBuffer::Bind(const Graphics& gfx)
{
	gfx.GetContext()->IASetIndexBuffer(m_pBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

//required for draw indexed I guess?
UINT IndexBuffer::GetSize() const
{
	return m_IndexBuffer.size();
}


